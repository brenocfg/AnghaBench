#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  nummapbrushes ; 
 int /*<<< orphan*/  nummapbrushsides ; 

void PrintMapInfo(void)
{
	Log_Print("\n");
	Log_Print("%6i brushes\n", nummapbrushes);
	Log_Print("%6i brush sides\n", nummapbrushsides);
//	Log_Print("%6i clipbrushes\n", c_clipbrushes);
//	Log_Print("%6i total sides\n", nummapbrushsides);
//	Log_Print("%6i boxbevels\n", c_boxbevels);
//	Log_Print("%6i edgebevels\n", c_edgebevels);
//	Log_Print("%6i entities\n", num_entities);
//	Log_Print("%6i planes\n", nummapplanes);
//	Log_Print("%6i areaportals\n", c_areaportals);
//	Log_Print("%6i squatt brushes\n", c_squattbrushes);
//	Log_Print("size: %5.0f,%5.0f,%5.0f to %5.0f,%5.0f,%5.0f\n", map_mins[0],map_mins[1],map_mins[2],
//		map_maxs[0],map_maxs[1],map_maxs[2]);
}