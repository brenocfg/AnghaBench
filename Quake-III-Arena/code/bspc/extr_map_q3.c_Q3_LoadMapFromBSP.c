#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int member_1; int member_2; } ;
typedef  TYPE_1__ vec3_t ;
struct quakefile_s {int /*<<< orphan*/  filename; } ;
struct TYPE_6__ {int numbrushes; } ;
struct TYPE_5__ {scalar_t__ numsides; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CreateCurveBrushes () ; 
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  MAPTYPE_QUAKE3 ; 
 int MAX_MAPFILE_BRUSHES ; 
 int /*<<< orphan*/  Q3_LoadBSPFile (struct quakefile_s*) ; 
 int /*<<< orphan*/  Q3_ParseBSPEntity (int) ; 
 int /*<<< orphan*/  Q3_ParseEntities () ; 
 int* brushmodelnumbers ; 
 TYPE_3__* entities ; 
 int /*<<< orphan*/  loadedmaptype ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 TYPE_2__* mapbrushes ; 
 int num_entities ; 
 scalar_t__ nummapbrushsides ; 

void Q3_LoadMapFromBSP(struct quakefile_s *qf)
{
	int i;
	vec3_t mins = {-1,-1,-1}, maxs = {1, 1, 1};

	Log_Print("-- Q3_LoadMapFromBSP --\n");
	//loaded map type
	loadedmaptype = MAPTYPE_QUAKE3;

	Log_Print("Loading map from %s...\n", qf->filename);
	//load the bsp file
	Q3_LoadBSPFile(qf);

	//create an index from bsp planes to map planes
	//DPlanes2MapPlanes();
	//clear brush model numbers
	for (i = 0; i < MAX_MAPFILE_BRUSHES; i++)
		brushmodelnumbers[i] = -1;

	nummapbrushsides = 0;
	num_entities = 0;

	Q3_ParseEntities();
	//
	for (i = 0; i < num_entities; i++)
	{
		Q3_ParseBSPEntity(i);
	} //end for

	AAS_CreateCurveBrushes();
	//get the map mins and maxs from the world model
	ClearBounds(map_mins, map_maxs);
	for (i = 0; i < entities[0].numbrushes; i++)
	{
		if (mapbrushes[i].numsides <= 0)
			continue;
		AddPointToBounds (mapbrushes[i].mins, map_mins, map_maxs);
		AddPointToBounds (mapbrushes[i].maxs, map_mins, map_maxs);
	} //end for
	/*/
	for (i = 0; i < nummapbrushes; i++)
	{
		//if (!mapbrushes[i].original_sides) continue;
		//AddBrushBevels(&mapbrushes[i]);
		//AAS_ExpandMapBrush(&mapbrushes[i], mins, maxs);
	} //end for*/
	/*
	for (i = 0; i < nummapbrushsides; i++)
	{
		Log_Write("side %d flags = %d", i, brushsides[i].flags);
	} //end for
	for (i = 0; i < nummapbrushes; i++)
	{
		Log_Write("brush contents: ");
		PrintContents(mapbrushes[i].contents);
		Log_Print("\n");
	} //end for*/
}