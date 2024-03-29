#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include "guiatlf.h"

using namespace std;

int main() {
    Guia_Tlf uno;

    assert(uno.begin() == uno.end());

    fstream input_data("datos/telefonos.txt", fstream::in);
    input_data >> uno;

    Guia_Tlf dos(uno);
    assert(dos.begin() != dos.end());
    
    cout << "\n///////// Primera salida de la guia 1 /////////" << endl;
    cout << uno << endl;

    uno.insert("Manolo", "666666666");
    
    cout << "\n///////// Segunda salida de la guia 1 /////////" << endl;
    cout << uno << endl;

    assert(uno["Pedro"] == dos["Pedro"]);
    uno["Pedro"][3] = '7';
    assert(uno["Pedro"] != dos["Pedro"]);

    uno = uno;
    assert(*uno.begin() == *dos.begin());

    Guia_Tlf tres;
    Guia_Tlf cuatro(tres);
    assert(tres.cbegin() == tres.cend());
    assert(cuatro.cbegin() == cuatro.cend());
    tres = uno;

    tres["Manolo"][0] = 0;
    assert(uno["Manolo"] != tres["Manolo"]);

    Guia_Tlf cinco = uno - dos;
    assert(cinco["Manolo"] == uno["Manolo"]);


    size_t c = 0;
    for (Guia_Tlf::iterator it = cinco.begin(); it != cinco.end(); ++it)
        //esto debe ejecutarse dos veces. Añadimos contador para que falle
        //si el diccionario contiene más elementos
        //Elementos esperados: Manolo y Pedro (porque a Pedro le hemos cambiado
        //un dígito)
        //usando (*it) en vez de it-> para evitar tener que sobrecargar -> en
        //caso de que el Guia_Tlf::iterator sea implementación propia
        assert(c++ < 2 && ((*it).first == "Manolo" || (*it).first == "Pedro"));

    //En la unión de diccionarios, cuando la clave existe en ambos, se puede
    //tomar el valor del primer diccionario o del segundo. Se aceptan ambos.
    Guia_Tlf seis = uno + dos;
    assert((seis["Pedro"] != uno["Pedro"] && seis["Pedro"] == dos["Pedro"])
            || (seis["Pedro"] == uno["Pedro"] && seis["Pedro"] != dos["Pedro"]));

    pair < std::map<string, string>::iterator, bool> p = seis.insert("Pedro", "123456789");
    assert(!p.second);
    
    // ---------------------- Probar funciones añadidas ------------------------- //
    
    cout << "\n///////// Prueba salida de página /////////" << endl;
    uno.insert("Ana", "677892689");
    uno.insert("Mario", "655782688");
    uno.imprimirPagina('A');
    uno.imprimirPagina('m');
    
    cout << "\n///////// Prueba salida de nombre /////////" << endl;
    uno.imprimirPersona("Pedro");
    uno.imprimirPersona("Paco");
    
    

    cout << "OK" << endl;

    return 0;
} 