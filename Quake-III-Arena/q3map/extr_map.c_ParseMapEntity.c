#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_10__ {struct TYPE_10__* next; } ;
typedef  TYPE_1__ epair_t ;
struct TYPE_11__ {scalar_t__* origin; TYPE_1__* epairs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AdjustBrushesForOrigin (TYPE_2__*) ; 
 scalar_t__ BPRIMIT_NEWBRUSHES ; 
 scalar_t__ BPRIMIT_OLDBRUSHES ; 
 int /*<<< orphan*/  Error (char*,...) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetVectorForKey (TYPE_2__*,char*,scalar_t__*) ; 
 size_t MAX_MAP_ENTITIES ; 
 int /*<<< orphan*/  MoveBrushesToWorld (TYPE_2__*) ; 
 int /*<<< orphan*/  ParseBrush () ; 
 TYPE_1__* ParseEpair () ; 
 int /*<<< orphan*/  ParsePatch () ; 
 int /*<<< orphan*/  ParseTerrain () ; 
 int /*<<< orphan*/  SetTerrainTextures () ; 
 int /*<<< orphan*/  UnGetToken () ; 
 char* ValueForKey (TYPE_2__*,char*) ; 
 TYPE_2__* entities ; 
 scalar_t__ entitySourceBrushes ; 
 scalar_t__ g_bBrushPrimit ; 
 TYPE_2__* mapent ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  numMapPatches ; 
 size_t num_entities ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  scriptline ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* token ; 

qboolean	ParseMapEntity (void) {
	epair_t		*e;

	if (!GetToken (qtrue))
		return qfalse;

	if (strcmp (token, "{") )
	{
		Error ("ParseEntity: { not found, found %s on line %d - last entity was at: <%4.2f, %4.2f, %4.2f>...", token, scriptline, entities[num_entities].origin[0], entities[num_entities].origin[1], entities[num_entities].origin[2]);
	}
	
	if (num_entities == MAX_MAP_ENTITIES)
		Error ("num_entities == MAX_MAP_ENTITIES");

	entitySourceBrushes = 0;

	mapent = &entities[num_entities];
	num_entities++;
	memset (mapent, 0, sizeof(*mapent));

	do
	{
		if (!GetToken (qtrue))
			Error ("ParseEntity: EOF without closing brace");
		if (!strcmp (token, "}") )
			break;

		if (!strcmp (token, "{") ) {
			// parse a brush or patch
			if (!GetToken (qtrue))
				break;
			if ( !strcmp( token, "patchDef2" ) ) {
				numMapPatches++;
				ParsePatch();
			} else if ( !strcmp( token, "terrainDef" ) ) {
				ParseTerrain();
			} else if ( !strcmp( token, "brushDef" ) ) {
				if (g_bBrushPrimit==BPRIMIT_OLDBRUSHES)
					Error("old brush format not allowed in new brush format map");
				g_bBrushPrimit=BPRIMIT_NEWBRUSHES;
				// parse brush primitive
				ParseBrush();
			}
			else
			{
				if (g_bBrushPrimit==BPRIMIT_NEWBRUSHES)
					Error("new brush format not allowed in old brush format map");
				g_bBrushPrimit=BPRIMIT_OLDBRUSHES;
				// parse old brush format
				UnGetToken();
				ParseBrush();
			}
			entitySourceBrushes++;
		}
		else
		{
			// parse a key / value pair
			e = ParseEpair ();
			e->next = mapent->epairs;
			mapent->epairs = e;
		}
	} while (1);

	GetVectorForKey (mapent, "origin", mapent->origin);

	//
	// if there was an origin brush, offset all of the planes and texinfo
	// for all the brushes in the entity
	if (mapent->origin[0] || mapent->origin[1] || mapent->origin[2]) {
		AdjustBrushesForOrigin( mapent );
	}

  // group_info entities are just for editor grouping
  // ignored
  // FIXME: leak!
  if (!strcmp("group_info", ValueForKey (mapent, "classname")))
  {
    num_entities--;
    return qtrue;
  }

	// group entities are just for editor convenience
	// toss all brushes into the world entity
	if (!strcmp ("func_group", ValueForKey (mapent, "classname")))
	{
		if ( !strcmp ("1", ValueForKey (mapent, "terrain"))) {
			SetTerrainTextures();
		}
		MoveBrushesToWorld (mapent);
		num_entities--;
		return qtrue;
	}

	return qtrue;
}