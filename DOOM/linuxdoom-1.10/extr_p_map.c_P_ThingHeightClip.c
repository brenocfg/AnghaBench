#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ z; scalar_t__ floorz; scalar_t__ ceilingz; scalar_t__ height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ mobj_t ;
typedef  int boolean ;

/* Variables and functions */
 int /*<<< orphan*/  P_CheckPosition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tmceilingz ; 
 scalar_t__ tmfloorz ; 

boolean P_ThingHeightClip (mobj_t* thing)
{
    boolean		onfloor;
	
    onfloor = (thing->z == thing->floorz);
	
    P_CheckPosition (thing, thing->x, thing->y);	
    // what about stranding a monster partially off an edge?
	
    thing->floorz = tmfloorz;
    thing->ceilingz = tmceilingz;
	
    if (onfloor)
    {
	// walking monsters rise and fall with the floor
	thing->z = thing->floorz;
    }
    else
    {
	// don't adjust a floating monster unless forced to
	if (thing->z+thing->height > thing->ceilingz)
	    thing->z = thing->ceilingz - thing->height;
    }
	
    if (thing->ceilingz - thing->floorz < thing->height)
	return false;
		
    return true;
}