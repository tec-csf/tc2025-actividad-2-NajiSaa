//
//  main.c
//
//Created by Naji M A Saadat A01025599 on 25/08/20.
//Copyright B) 2020 Naji M A Saadat A01025599. All rights reserved.
//
//
//Escriba un programa en C que permita recorrer un arreglo de cualquier tipo
//de datos utilizando diferentes tipos de Iteratores (Forward Iterator,
//Reverse Iterator, Bidirectional Iterator).
//
//Demuestre el funcionamiento del programa de la siguiente manera:
//
//Recorriendo un arreglo de números enteros utilizando un Forward Iterator.
//Recorriendo un arreglo de estructuras del tipo Libro, utilizando un
//Bidirectional Iterator.
//struct  Libro {
//char *titulo;
//int paginas;
//}
//El Iterator debe contener, al menos, las siguientes funcionalidades:
//
//begin :  Regresa un apuntador al primer elemento
//end : Regresa un apuntador al último elemento
//next : Regresa un apuntador al siguiente elemento. Si se llegó al final
//debe regresar NULL.
//prev : Regresa un apuntador al elemento anterior. Si llegó al inicio debe
//regresar NULL.
//Tenga en cuenta que debe existir una función genérica denominada Recorre
//que debe recibir como parámetros un arreglo de cualquier tipo y un
//Iterator de cualquier tipo y debe recorrer el arreglo utilizando el
//Iterator especificado y mostrar el contenido del arreglo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#define N 5
typedef struct
{
    char *titulo;
    int paginas;
}
Libro;

typedef void(*Imprimir)(void*);
typedef void(*Iterador)(void *, Imprimir *, size_t);
void recorrerIT(void *, Iterador *, Imprimir *, size_t);
void *begin(void *, size_t);
void *end(void *, size_t);
void *next(void *, size_t);
void *prev(void *, size_t);
void ImprimirInt(void*);
void ImprimirFloat(void*);
void ImprimirLibro(void*);
void forward(void *, Imprimir *, size_t);
void backward(void *, Imprimir *, size_t);
void bidirectional(void *, Imprimir *, size_t);

int
main(int argc, const char *argv[])
{
    printf("\t\t*** Bidirectional Iteration ***\n");
    printf("\t \t*** Naji M A Saadat A01025599 ***\n\n");
    int i = 1;
    int *Arreglo = (int*) malloc(N* sizeof(int));
    int *last = Arreglo + N;

    for (int *aux = Arreglo; aux < last; ++aux)
    {
        *aux = i++;
    }
    Imprimir *Fresult = (Imprimir*) malloc(sizeof(Imprimir));
    *Fresult = ImprimirInt;

    Iterador *it = (Iterador*) malloc(sizeof(Iterador));
    *it = forward;

    size_t posicion = sizeof(int);

    recorrerIT(Arreglo, it, Fresult, posicion);

    Libro *Libros = (Libro*) malloc(N* sizeof(Libro));
    Libro *UltimoLibro = Libros + N;
    int j = 0;
    for (Libro *Libro = Libros; Libro < UltimoLibro; ++Libro)
    {
        Libro->titulo = (char*) malloc(sizeof(char) *40);
        strcpy(Libro->titulo, "Progra Avanzada Activ 2");
        j += 111;
        Libro->paginas = j;
    }
    posicion = sizeof(Libro);
    *it = bidirectional;
    *Fresult = ImprimirLibro;
    recorrerIT(Libros, it, Fresult, posicion);
    
    free(Fresult);
    free(it);
    free(Arreglo);

    for (Libro *Libro = Libros; Libro < UltimoLibro; Libro++)
    {
        free(Libro->titulo);
    }
    free(Libros);
    return 0;
}

void
recorrerIT(void *vector, Iterador *it, Imprimir *Fresult, size_t posicion)
{
    (*it)(vector, Fresult, posicion);
}

void *
    begin(void *Arreglo, size_t posicion)
    {
        void *aux = Arreglo;
        return aux;
    }

void *
    end(void *Arreglo, size_t posicion)
    {
        void *aux = Arreglo;
        int i = 0;
        while (i < N)
        {
            i++;
            aux = aux + posicion;
        }
        return aux - posicion;
    }

void *
    next(void *Arreglo, size_t posicion)
    {
        void *aux = Arreglo + posicion;
        if (aux == NULL)
        {
            return NULL;
        }
        return aux;
    }

void *
    prev(void *Arreglo, size_t posicion)
    {
        void *aux = Arreglo - posicion;
        if (aux == NULL)
        {
            return NULL;
        }
        return aux;
    }

void
backward(void *vector, Imprimir *Fresult, size_t posicion)
{
    printf("\t\t**Backward Iteration **\n\n");
    void *aux = end(vector, posicion);
    int i = 0;
    do {
        printf("**");
        (*Fresult)(aux);
        aux = prev(aux, posicion);
        i++;
    }
    while (i < N);
    printf("\n");
}

void
forward(void *vector, Imprimir *Fresult, size_t posicion)
{
    printf("\t\t ** Forward Iteration **\n\n");
    void *aux = begin(vector, posicion);
    int i = 0;
    do {
        printf("**");
        (*Fresult)(aux);
        aux = next(aux, posicion);
        i++;
    }
    while (i < N);
    printf("\n");
}

void
bidirectional(void *vector, Imprimir *Fresult, size_t posicion)
{
    printf("\t \t ** Bidirectional Iteration **\n");
    forward(vector, Fresult, posicion);
    backward(vector, Fresult, posicion);
}

void
ImprimirLibro(void *posicion)
{
    Libro *aux = posicion;
    printf("*Titulo: %s\n", aux->titulo);
    printf("*Paginas: %d\n", aux->paginas);
    printf("\n");
}

void
ImprimirInt(void *posicion)
{
    int *Valor = (int*) posicion;
    printf("%d \n", *Valor);
}


