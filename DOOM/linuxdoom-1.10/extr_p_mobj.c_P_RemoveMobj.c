#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thinker_t ;
struct TYPE_5__ {int flags; scalar_t__ type; int /*<<< orphan*/  spawnpoint; } ;
typedef  TYPE_1__ mobj_t ;

/* Variables and functions */
 int ITEMQUESIZE ; 
 int MF_DROPPED ; 
 int MF_SPECIAL ; 
 scalar_t__ MT_INS ; 
 scalar_t__ MT_INV ; 
 int /*<<< orphan*/  P_RemoveThinker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  P_UnsetThingPosition (TYPE_1__*) ; 
 int /*<<< orphan*/  S_StopSound (TYPE_1__*) ; 
 size_t iquehead ; 
 size_t iquetail ; 
 int /*<<< orphan*/ * itemrespawnque ; 
 int /*<<< orphan*/ * itemrespawntime ; 
 int /*<<< orphan*/  leveltime ; 

void P_RemoveMobj (mobj_t* mobj)
{
    if ((mobj->flags & MF_SPECIAL)
	&& !(mobj->flags & MF_DROPPED)
	&& (mobj->type != MT_INV)
	&& (mobj->type != MT_INS))
    {
	itemrespawnque[iquehead] = mobj->spawnpoint;
	itemrespawntime[iquehead] = leveltime;
	iquehead = (iquehead+1)&(ITEMQUESIZE-1);

	// lose one off the end?
	if (iquehead == iquetail)
	    iquetail = (iquetail+1)&(ITEMQUESIZE-1);
    }
	
    // unlink from sector and block lists
    P_UnsetThingPosition (mobj);
    
    // stop any playing sound
    S_StopSound (mobj);
    
    // free block
    P_RemoveThinker ((thinker_t*)mobj);
}