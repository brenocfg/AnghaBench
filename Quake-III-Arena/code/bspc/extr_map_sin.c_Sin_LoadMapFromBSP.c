#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numbrushes; } ;
struct TYPE_3__ {int* mins; int* maxs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  MAPTYPE_SIN ; 
 int MAX_MAPFILE_BRUSHES ; 
 int /*<<< orphan*/  Sin_CreateMapTexinfo () ; 
 int /*<<< orphan*/  Sin_LoadBSPFile (char*,int,int) ; 
 int /*<<< orphan*/  Sin_ParseBSPEntity (int) ; 
 int /*<<< orphan*/  Sin_ParseEntities () ; 
 int* brushmodelnumbers ; 
 TYPE_2__* entities ; 
 int /*<<< orphan*/  loadedmaptype ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 TYPE_1__* mapbrushes ; 
 int num_entities ; 
 scalar_t__ nummapbrushsides ; 

void Sin_LoadMapFromBSP(char *filename, int offset, int length)
{
	int i;

	Log_Print("-- Sin_LoadMapFromBSP --\n");
	//loaded map type
	loadedmaptype = MAPTYPE_SIN;

	Log_Print("Loading map from %s...\n", filename);
	//load the bsp file
	Sin_LoadBSPFile(filename, offset, length);

	//create an index from bsp planes to map planes
	//DPlanes2MapPlanes();
	//clear brush model numbers
	for (i = 0; i < MAX_MAPFILE_BRUSHES; i++)
		brushmodelnumbers[i] = -1;

	nummapbrushsides = 0;
	num_entities = 0;

	Sin_ParseEntities();
	//
	for (i = 0; i < num_entities; i++)
	{
		Sin_ParseBSPEntity(i);
	} //end for

	//get the map mins and maxs from the world model
	ClearBounds(map_mins, map_maxs);
	for (i = 0; i < entities[0].numbrushes; i++)
	{
		if (mapbrushes[i].mins[0] > 4096)
			continue;	//no valid points
		AddPointToBounds (mapbrushes[i].mins, map_mins, map_maxs);
		AddPointToBounds (mapbrushes[i].maxs, map_mins, map_maxs);
	} //end for
	//
	Sin_CreateMapTexinfo();
}