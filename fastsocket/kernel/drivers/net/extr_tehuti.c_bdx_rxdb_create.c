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
struct rxdb {int* stack; int nelem; int top; void* elems; } ;
struct rx_map {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct rxdb* vmalloc (int) ; 

__attribute__((used)) static struct rxdb *bdx_rxdb_create(int nelem)
{
	struct rxdb *db;
	int i;

	db = vmalloc(sizeof(struct rxdb)
		     + (nelem * sizeof(int))
		     + (nelem * sizeof(struct rx_map)));
	if (likely(db != NULL)) {
		db->stack = (int *)(db + 1);
		db->elems = (void *)(db->stack + nelem);
		db->nelem = nelem;
		db->top = nelem;
		for (i = 0; i < nelem; i++)
			db->stack[i] = nelem - i - 1;	/* to make first allocs
							   close to db struct*/
	}

	return db;
}