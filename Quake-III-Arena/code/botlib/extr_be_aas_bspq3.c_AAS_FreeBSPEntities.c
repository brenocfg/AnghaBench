#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* value; struct TYPE_5__* key; struct TYPE_5__* next; } ;
typedef  TYPE_1__ bsp_epair_t ;
struct TYPE_6__ {TYPE_1__* epairs; } ;
typedef  TYPE_2__ bsp_entity_t ;
struct TYPE_7__ {int numentities; TYPE_2__* entities; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 TYPE_3__ bspworld ; 

void AAS_FreeBSPEntities(void)
{
	int i;
	bsp_entity_t *ent;
	bsp_epair_t *epair, *nextepair;

	for (i = 1; i < bspworld.numentities; i++)
	{
		ent = &bspworld.entities[i];
		for (epair = ent->epairs; epair; epair = nextepair)
		{
			nextepair = epair->next;
			//
			if (epair->key) FreeMemory(epair->key);
			if (epair->value) FreeMemory(epair->value);
			FreeMemory(epair);
		} //end for
	} //end for
	bspworld.numentities = 0;
}