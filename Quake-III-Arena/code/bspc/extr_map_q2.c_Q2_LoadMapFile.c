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
typedef  int /*<<< orphan*/  script_t ;
struct TYPE_4__ {int numbrushes; } ;
struct TYPE_3__ {int* mins; int* maxs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBounds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeScript (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadScriptFile (char*) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  MAPTYPE_QUAKE2 ; 
 int /*<<< orphan*/  PrintMapInfo () ; 
 int /*<<< orphan*/  Q2_CreateMapTexinfo () ; 
 scalar_t__ Q2_ParseMapEntity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetMapLoading () ; 
 int SCFL_NOSTRINGESCAPECHARS ; 
 int SCFL_NOSTRINGWHITESPACES ; 
 int SCFL_PRIMITIVE ; 
 int /*<<< orphan*/  SetScriptFlags (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* entities ; 
 int /*<<< orphan*/  loadedmaptype ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 TYPE_1__* mapbrushes ; 
 scalar_t__ num_entities ; 
 scalar_t__ nummapbrushsides ; 

void Q2_LoadMapFile(char *filename)
{		
	int i;
	script_t *script;

	Log_Print("-- Q2_LoadMapFile --\n");
#ifdef ME
	//loaded map type
	loadedmaptype = MAPTYPE_QUAKE2;
	//reset the map loading
	ResetMapLoading();
#endif //ME

	script = LoadScriptFile(filename);
	if (!script)
	{
		Log_Print("couldn't open %s\n", filename);
		return;
	} //end if
	//white spaces and escape characters inside a string are not allowed
	SetScriptFlags(script, SCFL_NOSTRINGWHITESPACES |
									SCFL_NOSTRINGESCAPECHARS |
									SCFL_PRIMITIVE);

	nummapbrushsides = 0;
	num_entities = 0;
	
	while (Q2_ParseMapEntity(script))
	{
	}

	ClearBounds (map_mins, map_maxs);
	for (i=0 ; i<entities[0].numbrushes ; i++)
	{
		if (mapbrushes[i].mins[0] > 4096)
			continue;	// no valid points
		AddPointToBounds (mapbrushes[i].mins, map_mins, map_maxs);
		AddPointToBounds (mapbrushes[i].maxs, map_mins, map_maxs);
	} //end for

	PrintMapInfo();

	//free the script
	FreeScript(script);
//	TestExpandBrushes ();
	//
	Q2_CreateMapTexinfo();
}