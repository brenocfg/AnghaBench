#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int texinfo; int /*<<< orphan*/  flags; int /*<<< orphan*/  planenum; scalar_t__ surf; int /*<<< orphan*/  contents; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_17__ {int leafnum; int numsides; int /*<<< orphan*/  contents; TYPE_2__* original_sides; scalar_t__ brushnum; TYPE_4__* entitynum; } ;
typedef  TYPE_3__ mapbrush_t ;
struct TYPE_18__ {int /*<<< orphan*/  numbrushes; scalar_t__ firstbrush; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_19__ {int numsides; int /*<<< orphan*/  side; TYPE_1__* sides; } ;
typedef  TYPE_5__ bspbrush_t ;
struct TYPE_15__ {int texinfo; int /*<<< orphan*/  planenum; int /*<<< orphan*/  winding; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CreateMapBrushes (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  AddBrushBevels (TYPE_3__*) ; 
 int /*<<< orphan*/  CheckBSPBrush (TYPE_5__*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAPFILE_BRUSHES ; 
 size_t MAX_MAPFILE_BRUSHSIDES ; 
 int /*<<< orphan*/  MakeBrushWindings (TYPE_3__*) ; 
 int /*<<< orphan*/  SFL_TEXTURED ; 
 int TEXINFO_NODE ; 
 TYPE_2__* brushsides ; 
 scalar_t__ create_aas ; 
 int entities ; 
 TYPE_3__* mapbrushes ; 
 size_t nummapbrushes ; 
 size_t nummapbrushsides ; 
 int /*<<< orphan*/  q1_numclipbrushes ; 

void Q1_BSPBrushToMapBrush(bspbrush_t *bspbrush, entity_t *mapent)
{
	mapbrush_t *mapbrush;
	side_t *side;
	int i, besttexinfo;

	CheckBSPBrush(bspbrush);

	if (nummapbrushes >= MAX_MAPFILE_BRUSHES)
	Error ("nummapbrushes == MAX_MAPFILE_BRUSHES");

	mapbrush = &mapbrushes[nummapbrushes];
	mapbrush->original_sides = &brushsides[nummapbrushsides];
	mapbrush->entitynum = mapent - entities;
	mapbrush->brushnum = nummapbrushes - mapent->firstbrush;
	mapbrush->leafnum = -1;
	mapbrush->numsides = 0;

	besttexinfo = TEXINFO_NODE;
	for (i = 0; i < bspbrush->numsides; i++)
	{
		if (!bspbrush->sides[i].winding) continue;
		//
		if (nummapbrushsides >= MAX_MAPFILE_BRUSHSIDES)
			Error ("MAX_MAPFILE_BRUSHSIDES");
		side = &brushsides[nummapbrushsides];
		//the contents of the bsp brush is stored in the side variable
		side->contents = bspbrush->side;
		side->surf = 0;
		side->planenum = bspbrush->sides[i].planenum;
		side->texinfo = bspbrush->sides[i].texinfo;
		if (side->texinfo != TEXINFO_NODE)
		{
			//this brush side is textured
			side->flags |= SFL_TEXTURED;
			besttexinfo = side->texinfo;
		} //end if
		//
		nummapbrushsides++;
		mapbrush->numsides++;
	} //end for
	//
	if (besttexinfo == TEXINFO_NODE)
	{
		mapbrush->numsides = 0;
		q1_numclipbrushes++;
		return;
	} //end if
	//set the texinfo for all the brush sides without texture
	for (i = 0; i < mapbrush->numsides; i++)
	{
		if (mapbrush->original_sides[i].texinfo == TEXINFO_NODE)
		{
			mapbrush->original_sides[i].texinfo = besttexinfo;
		} //end if
	} //end for
	//contents of the brush
	mapbrush->contents = bspbrush->side;
	//
	if (create_aas)
	{
		//create the AAS brushes from this brush, add brush bevels
		AAS_CreateMapBrushes(mapbrush, mapent, true);
		return;
	} //end if
	//create windings for sides and bounds for brush
	MakeBrushWindings(mapbrush);
	//add brush bevels
	AddBrushBevels(mapbrush);
	//a new brush has been created
	nummapbrushes++;
	mapent->numbrushes++;
}