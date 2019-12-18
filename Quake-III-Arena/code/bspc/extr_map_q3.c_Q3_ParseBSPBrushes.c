#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t modelnum; } ;
typedef  TYPE_1__ entity_t ;
struct TYPE_6__ {int numBrushes; int firstBrush; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q3_BSPBrushToMapBrush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * q3_dbrushes ; 
 TYPE_2__* q3_dmodels ; 

void Q3_ParseBSPBrushes(entity_t *mapent)
{
	int i;

	for (i = 0; i < q3_dmodels[mapent->modelnum].numBrushes; i++)
	{
		Q3_BSPBrushToMapBrush(&q3_dbrushes[q3_dmodels[mapent->modelnum].firstBrush + i], mapent);
	} //end for
}