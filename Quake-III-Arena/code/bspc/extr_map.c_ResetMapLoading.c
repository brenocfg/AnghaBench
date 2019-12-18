#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  side_t ;
typedef  int /*<<< orphan*/  plane_t ;
typedef  int /*<<< orphan*/  mapbrush_t ;
typedef  int /*<<< orphan*/  map_texinfo_t ;
struct TYPE_11__ {struct TYPE_11__* value; struct TYPE_11__* key; struct TYPE_11__* next; } ;
typedef  TYPE_1__ epair_t ;
typedef  int /*<<< orphan*/  entity_t ;
typedef  int /*<<< orphan*/  brush_texture_t ;
struct TYPE_12__ {TYPE_1__* epairs; scalar_t__ winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeWinding (scalar_t__) ; 
 int MAX_MAPFILE_BRUSHES ; 
 int MAX_MAPFILE_BRUSHSIDES ; 
 int MAX_MAPFILE_PLANES ; 
 int MAX_MAPFILE_TEXINFO ; 
 int MAX_MAP_ENTITIES ; 
 int PLANE_HASHES ; 
 int /*<<< orphan*/  Q2_ResetMapLoading () ; 
 int /*<<< orphan*/  Sin_ResetMapLoading () ; 
 int /*<<< orphan*/  VectorClear (int /*<<< orphan*/ ) ; 
 TYPE_2__* brushsides ; 
 scalar_t__ c_areaportals ; 
 scalar_t__ c_boxbevels ; 
 scalar_t__ c_clipbrushes ; 
 scalar_t__ c_edgebevels ; 
 scalar_t__ c_writtenbrushes ; 
 TYPE_2__* entities ; 
 int /*<<< orphan*/  map_maxs ; 
 int /*<<< orphan*/  map_mins ; 
 scalar_t__ map_numtexinfo ; 
 TYPE_2__* map_texinfo ; 
 TYPE_2__* mapbrushes ; 
 TYPE_2__* mapplanes ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int num_entities ; 
 scalar_t__ nummapbrushes ; 
 int nummapbrushsides ; 
 scalar_t__ nummapplanes ; 
 TYPE_2__* planehash ; 
 TYPE_2__* side_brushtextures ; 

void ResetMapLoading(void)
{
	int i;
	epair_t *ep, *nextep;

	Q2_ResetMapLoading();
	Sin_ResetMapLoading();

	//free all map brush side windings
	for (i = 0; i < nummapbrushsides; i++)
	{
		if (brushsides[i].winding)
		{
			FreeWinding(brushsides[i].winding);
		} //end for
	} //end for

	//reset regular stuff
	nummapbrushes = 0;
	memset(mapbrushes, 0, MAX_MAPFILE_BRUSHES * sizeof(mapbrush_t));
	//
	nummapbrushsides = 0;
	memset(brushsides, 0, MAX_MAPFILE_BRUSHSIDES * sizeof(side_t));
	memset(side_brushtextures, 0, MAX_MAPFILE_BRUSHSIDES * sizeof(brush_texture_t));
	//
	nummapplanes = 0;
	memset(mapplanes, 0, MAX_MAPFILE_PLANES * sizeof(plane_t));
	//
	memset(planehash, 0, PLANE_HASHES * sizeof(plane_t *));
	//
	memset(map_texinfo, 0, MAX_MAPFILE_TEXINFO * sizeof(map_texinfo_t));
	map_numtexinfo = 0;
	//
	VectorClear(map_mins);
	VectorClear(map_maxs);
	//
	c_boxbevels = 0;
	c_edgebevels = 0;
	c_areaportals = 0;
	c_clipbrushes = 0;
	c_writtenbrushes = 0;
	//clear the entities
	for (i = 0; i < num_entities; i++)
	{
		for (ep = entities[i].epairs; ep; ep = nextep)
		{
			nextep = ep->next;
			FreeMemory(ep->key);
			FreeMemory(ep->value);
			FreeMemory(ep);
		} //end for
	} //end for
	num_entities = 0;
	memset(entities, 0, MAX_MAP_ENTITIES * sizeof(entity_t));
}