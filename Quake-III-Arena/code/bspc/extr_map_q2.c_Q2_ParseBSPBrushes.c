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
struct TYPE_5__ {scalar_t__ modelnum; } ;
typedef  TYPE_1__ entity_t ;

/* Variables and functions */
 int /*<<< orphan*/  Q2_BSPBrushToMapBrush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Q2_SetBrushModelNumbers (TYPE_1__*) ; 
 scalar_t__* brushmodelnumbers ; 
 int /*<<< orphan*/ * dbrushes ; 
 int numbrushes ; 

void Q2_ParseBSPBrushes(entity_t *mapent)
{
	int i;

	//give all the brushes that belong to this entity the number of the
	//BSP model used by this entity
	Q2_SetBrushModelNumbers(mapent);
	//now parse all the brushes with the correct mapent->modelnum
	for (i = 0; i < numbrushes; i++)
	{
		if (brushmodelnumbers[i] == mapent->modelnum)
		{
			Q2_BSPBrushToMapBrush(&dbrushes[i], mapent);
		} //end if
	} //end for
}