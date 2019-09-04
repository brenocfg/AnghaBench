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
struct malloc_header {int size; scalar_t__ used; } ;

/* Variables and functions */
 scalar_t__ e_heap ; 

void free(void *v_addr)
{
	struct malloc_header *bl, *nextbl;

	/* Calcul du debut du bloc */
	bl = (struct malloc_header *) (v_addr - sizeof(struct malloc_header));

	/* 
	 * On merge le bloc nouvellement libere avec le bloc suivant ci celui-ci
	 * est aussi libre
	 */
	while ((nextbl = (struct malloc_header *) ((char *) bl + bl->size))
             && nextbl < (struct malloc_header *) e_heap
	     && nextbl->used == 0) 
			bl->size += nextbl->size;

	/* On libere le bloc alloue */
	bl->used = 0;
}