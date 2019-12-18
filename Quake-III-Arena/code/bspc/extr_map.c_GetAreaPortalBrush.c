#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ entitynum; int contents; } ;
typedef  TYPE_1__ mapbrush_t ;
struct TYPE_7__ {int areaportalnum; } ;
typedef  TYPE_2__ entity_t ;

/* Variables and functions */
 int CONTENTS_AREAPORTAL ; 
 int /*<<< orphan*/  Log_Print (char*,int) ; 
 TYPE_1__* mapbrushes ; 
 int nummapbrushes ; 

mapbrush_t *GetAreaPortalBrush(entity_t *mapent)
{
	int portalnum, bn;
	mapbrush_t *brush;

	//the area portal number
	portalnum = mapent->areaportalnum;
	//find the area portal brush in the world brushes
	for (bn = 0; bn < nummapbrushes && portalnum; bn++)
	{
		brush = &mapbrushes[bn];
		//must be in world entity
		if (brush->entitynum == 0)
		{
			if (brush->contents & CONTENTS_AREAPORTAL)
			{
				portalnum--;
			} //end if
		} //end if
	} //end for
	if (bn < nummapbrushes)
	{
		return brush;
	} //end if
	else
	{
		Log_Print("area portal %d brush not found\n", mapent->areaportalnum);
		return NULL;
	} //end else
}