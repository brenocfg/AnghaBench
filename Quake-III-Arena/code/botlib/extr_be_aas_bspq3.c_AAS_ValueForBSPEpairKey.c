#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct TYPE_5__* next; } ;
typedef  TYPE_2__ bsp_epair_t ;
struct TYPE_6__ {TYPE_1__* entities; } ;
struct TYPE_4__ {TYPE_2__* epairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_BSPEntityInRange (int) ; 
 TYPE_3__ bspworld ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

int AAS_ValueForBSPEpairKey(int ent, char *key, char *value, int size)
{
	bsp_epair_t *epair;

	value[0] = '\0';
	if (!AAS_BSPEntityInRange(ent)) return qfalse;
	for (epair = bspworld.entities[ent].epairs; epair; epair = epair->next)
	{
		if (!strcmp(epair->key, key))
		{
			strncpy(value, epair->value, size-1);
			value[size-1] = '\0';
			return qtrue;
		} //end if
	} //end for
	return qfalse;
}