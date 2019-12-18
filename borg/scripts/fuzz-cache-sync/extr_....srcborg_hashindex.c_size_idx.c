#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int NELEMS (int*) ; 
 int* hash_sizes ; 

int size_idx(int size){
    /* find the hash_sizes index with entry >= size */
    int elems = NELEMS(hash_sizes);
    int entry, i=0;
    do{
        entry = hash_sizes[i++];
    }while((entry < size) && (i < elems));
    if (i >= elems)
        return elems - 1;
    i--;
    return i;
}