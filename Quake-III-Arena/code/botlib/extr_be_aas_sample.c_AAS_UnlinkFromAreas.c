#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t areanum; TYPE_2__* prev_ent; TYPE_1__* next_ent; struct TYPE_9__* next_area; } ;
typedef  TYPE_3__ aas_link_t ;
struct TYPE_10__ {TYPE_1__** arealinkedentities; } ;
struct TYPE_8__ {TYPE_1__* next_ent; } ;
struct TYPE_7__ {TYPE_2__* prev_ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DeAllocAASLink (TYPE_3__*) ; 
 TYPE_4__ aasworld ; 

void AAS_UnlinkFromAreas(aas_link_t *areas)
{
	aas_link_t *link, *nextlink;

	for (link = areas; link; link = nextlink)
	{
		//next area the entity is linked in
		nextlink = link->next_area;
		//remove the entity from the linked list of this area
		if (link->prev_ent) link->prev_ent->next_ent = link->next_ent;
		else aasworld.arealinkedentities[link->areanum] = link->next_ent;
		if (link->next_ent) link->next_ent->prev_ent = link->prev_ent;
		//deallocate the link structure
		AAS_DeAllocAASLink(link);
	} //end for
}