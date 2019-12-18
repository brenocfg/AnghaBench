#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ceilingheight; scalar_t__ floorheight; } ;
typedef  TYPE_1__ sector_t ;
struct TYPE_5__ {int* sidenum; TYPE_1__* backsector; TYPE_1__* frontsector; } ;
typedef  TYPE_2__ line_t ;

/* Variables and functions */
 scalar_t__ lowfloor ; 
 scalar_t__ openbottom ; 
 scalar_t__ openrange ; 
 scalar_t__ opentop ; 

void P_LineOpening (line_t* linedef)
{
    sector_t*	front;
    sector_t*	back;
	
    if (linedef->sidenum[1] == -1)
    {
	// single sided line
	openrange = 0;
	return;
    }
	 
    front = linedef->frontsector;
    back = linedef->backsector;
	
    if (front->ceilingheight < back->ceilingheight)
	opentop = front->ceilingheight;
    else
	opentop = back->ceilingheight;

    if (front->floorheight > back->floorheight)
    {
	openbottom = front->floorheight;
	lowfloor = back->floorheight;
    }
    else
    {
	openbottom = back->floorheight;
	lowfloor = front->floorheight;
    }
	
    openrange = opentop - openbottom;
}