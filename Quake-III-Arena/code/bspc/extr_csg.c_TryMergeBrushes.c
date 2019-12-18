#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int planenum; scalar_t__ texinfo; int /*<<< orphan*/  winding; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_13__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_14__ {scalar_t__* mins; scalar_t__* maxs; int numsides; TYPE_1__* sides; int /*<<< orphan*/  original; } ;
typedef  TYPE_3__ bspbrush_t ;

/* Variables and functions */
 TYPE_3__* AllocBrush (int) ; 
 int /*<<< orphan*/  BSPBrushWindings (TYPE_3__*) ; 
 int /*<<< orphan*/  BoundBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  CheckBSPBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 scalar_t__ TEXINFO_NODE ; 
 scalar_t__ WindingsNonConvex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mapplanes ; 

bspbrush_t *TryMergeBrushes(bspbrush_t *brush1, bspbrush_t *brush2)
{
	int i, j, k, n, shared;
	side_t *side1, *side2, *cs;
	plane_t *plane1, *plane2;
	bspbrush_t *newbrush;

	//check for bounding box overlapp
	for (i = 0; i < 3; i++)
	{
		if (brush1->mins[i] > brush2->maxs[i] + 2
				|| brush1->maxs[i] < brush2->mins[i] - 2)
		{
			return NULL;
		} //end if
	} //end for
	//
	shared = 0;
	//check if the brush is convex... flipped planes make a brush non-convex
	for (i = 0; i < brush1->numsides; i++)
	{
		side1 = &brush1->sides[i];
		//don't check the "shared" sides
		for (k = 0; k < brush2->numsides; k++)
		{
			side2 = &brush2->sides[k];
			if (side1->planenum == (side2->planenum^1))
			{
				shared++;
				//there may only be ONE shared side
				if (shared > 1) return NULL;
				break;
			} //end if
		} //end for
		if (k < brush2->numsides) continue;
		//
		for (j = 0; j < brush2->numsides; j++)
		{
			side2 = &brush2->sides[j];
			//don't check the "shared" sides
			for (n = 0; n < brush1->numsides; n++)
			{
				side1 = &brush1->sides[n];
				if (side1->planenum == (side2->planenum^1)) break;
			} //end for
			if (n < brush1->numsides) continue;
			//
			side1 = &brush1->sides[i];
			//if the side is in the same plane
			//*
			if (side1->planenum == side2->planenum)
			{
				if (side1->texinfo != TEXINFO_NODE &&
					side2->texinfo != TEXINFO_NODE &&
					side1->texinfo != side2->texinfo) return NULL;
				continue;
			} //end if
			//
			plane1 = &mapplanes[side1->planenum];
			plane2 = &mapplanes[side2->planenum];
			//
			if (WindingsNonConvex(side1->winding, side2->winding,
									plane1->normal, plane2->normal,
									plane1->dist, plane2->dist))
			{
				return NULL;
			} //end if
		} //end for
	} //end for
	newbrush = AllocBrush(brush1->numsides + brush2->numsides);
	newbrush->original = brush1->original;
	newbrush->numsides = 0;
	//newbrush->side = brush1->side;	//brush contents
	//fix texinfos for sides lying in the same plane
	for (i = 0; i < brush1->numsides; i++)
	{
		side1 = &brush1->sides[i];
		//
		for (n = 0; n < brush2->numsides; n++)
		{
			side2 = &brush2->sides[n];
			//if both sides are in the same plane get the texinfo right
			if (side1->planenum == side2->planenum)
			{
				if (side1->texinfo == TEXINFO_NODE) side1->texinfo = side2->texinfo;
				if (side2->texinfo == TEXINFO_NODE) side2->texinfo = side1->texinfo;
			} //end if
		} //end for
	} //end for
	//
	for (i = 0; i < brush1->numsides; i++)
	{
		side1 = &brush1->sides[i];
		//don't add the "shared" sides
		for (n = 0; n < brush2->numsides; n++)
		{
			side2 = &brush2->sides[n];
			if (side1->planenum == (side2->planenum ^ 1)) break;
		} //end for
		if (n < brush2->numsides) continue;
		//
		for (n = 0; n < newbrush->numsides; n++)
		{
			cs = &newbrush->sides[n];
			if (cs->planenum == side1->planenum)
			{
				Log_Print("brush duplicate plane\n");
				break;
			} //end if
		} //end if
		if (n < newbrush->numsides) continue;
		//add this side
		cs = &newbrush->sides[newbrush->numsides];
		newbrush->numsides++;
		*cs = *side1;
	} //end for
	for (j = 0; j < brush2->numsides; j++)
	{
		side2 = &brush2->sides[j];
		for (n = 0; n < brush1->numsides; n++)
		{
			side1 = &brush1->sides[n];
			//if the side is in the same plane
			if (side2->planenum == side1->planenum) break;
			//don't add the "shared" sides
			if (side2->planenum == (side1->planenum ^ 1)) break;
		} //end for
		if (n < brush1->numsides) continue;
		//
		for (n = 0; n < newbrush->numsides; n++)
		{
			cs = &newbrush->sides[n];
			if (cs->planenum == side2->planenum)
			{
				Log_Print("brush duplicate plane\n");
				break;
			} //end if
		} //end if
		if (n < newbrush->numsides) continue;
		//add this side
		cs = &newbrush->sides[newbrush->numsides];
		newbrush->numsides++;
		*cs = *side2;
	} //end for
	BSPBrushWindings(newbrush);
	BoundBrush(newbrush);
	CheckBSPBrush(newbrush);
	return newbrush;
}