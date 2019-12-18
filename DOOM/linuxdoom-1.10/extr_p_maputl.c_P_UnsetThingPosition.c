#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int flags; int x; int y; TYPE_7__* bnext; TYPE_5__* bprev; TYPE_4__* snext; TYPE_3__* subsector; TYPE_1__* sprev; } ;
typedef  TYPE_6__ mobj_t ;
struct TYPE_15__ {TYPE_5__* bprev; } ;
struct TYPE_13__ {TYPE_7__* bnext; } ;
struct TYPE_12__ {TYPE_1__* sprev; } ;
struct TYPE_11__ {TYPE_2__* sector; } ;
struct TYPE_10__ {TYPE_4__* thinglist; } ;
struct TYPE_9__ {TYPE_4__* snext; } ;

/* Variables and functions */
 int MAPBLOCKSHIFT ; 
 int MF_NOBLOCKMAP ; 
 int MF_NOSECTOR ; 
 TYPE_7__** blocklinks ; 
 int bmapheight ; 
 int bmaporgx ; 
 int bmaporgy ; 
 int bmapwidth ; 

void P_UnsetThingPosition (mobj_t* thing)
{
    int		blockx;
    int		blocky;

    if ( ! (thing->flags & MF_NOSECTOR) )
    {
	// inert things don't need to be in blockmap?
	// unlink from subsector
	if (thing->snext)
	    thing->snext->sprev = thing->sprev;

	if (thing->sprev)
	    thing->sprev->snext = thing->snext;
	else
	    thing->subsector->sector->thinglist = thing->snext;
    }
	
    if ( ! (thing->flags & MF_NOBLOCKMAP) )
    {
	// inert things don't need to be in blockmap
	// unlink from block map
	if (thing->bnext)
	    thing->bnext->bprev = thing->bprev;
	
	if (thing->bprev)
	    thing->bprev->bnext = thing->bnext;
	else
	{
	    blockx = (thing->x - bmaporgx)>>MAPBLOCKSHIFT;
	    blocky = (thing->y - bmaporgy)>>MAPBLOCKSHIFT;

	    if (blockx>=0 && blockx < bmapwidth
		&& blocky>=0 && blocky <bmapheight)
	    {
		blocklinks[blocky*bmapwidth+blockx] = thing->bnext;
	    }
	}
    }
}