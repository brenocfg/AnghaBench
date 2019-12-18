#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int contents; } ;
typedef  TYPE_1__ q1_dleaf_t ;
struct TYPE_13__ {struct TYPE_13__* next; int /*<<< orphan*/  side; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_15__ {int planenum; int* children; } ;
struct TYPE_14__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENTS_LAVA ; 
 int /*<<< orphan*/  CONTENTS_SLIME ; 
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 int /*<<< orphan*/  CONTENTS_WATER ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 int FindFloatPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBrush (TYPE_2__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
#define  Q1_CONTENTS_CLIP 142 
#define  Q1_CONTENTS_CURRENT_0 141 
#define  Q1_CONTENTS_CURRENT_180 140 
#define  Q1_CONTENTS_CURRENT_270 139 
#define  Q1_CONTENTS_CURRENT_90 138 
#define  Q1_CONTENTS_CURRENT_DOWN 137 
#define  Q1_CONTENTS_CURRENT_UP 136 
#define  Q1_CONTENTS_EMPTY 135 
#define  Q1_CONTENTS_LAVA 134 
#define  Q1_CONTENTS_ORIGIN 133 
#define  Q1_CONTENTS_SKY 132 
#define  Q1_CONTENTS_SLIME 131 
#define  Q1_CONTENTS_SOLID 130 
#define  Q1_CONTENTS_TRANSLUCENT 129 
#define  Q1_CONTENTS_WATER 128 
 int /*<<< orphan*/  Q1_SplitBrush (TYPE_2__*,int,int,TYPE_2__**,TYPE_2__**) ; 
 TYPE_1__* q1_dleafs ; 
 TYPE_4__* q1_dnodes ; 
 TYPE_3__* q1_dplanes ; 
 int /*<<< orphan*/  q1_numbrushes ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 

bspbrush_t *Q1_CreateBrushes_r(bspbrush_t *brush, int nodenum)
{
	int planenum;
	bspbrush_t *front, *back;
	q1_dleaf_t *leaf;

	//if it is a leaf
	if (nodenum < 0)
	{
		leaf = &q1_dleafs[(-nodenum) - 1];
		if (leaf->contents != Q1_CONTENTS_EMPTY)
		{
#ifdef Q1_PRINT
			qprintf("\r%5i", ++q1_numbrushes);
#endif //Q1_PRINT
		} //end if
		switch(leaf->contents)
		{
			case Q1_CONTENTS_EMPTY:
			{
				FreeBrush(brush);
				return NULL;
			} //end case
			case Q1_CONTENTS_SOLID:
#ifdef HLCONTENTS
			case Q1_CONTENTS_CLIP:
#endif HLCONTENTS
			case Q1_CONTENTS_SKY:
#ifdef HLCONTENTS
			case Q1_CONTENTS_TRANSLUCENT:
#endif HLCONTENTS
			{
				brush->side = CONTENTS_SOLID;
				return brush;
			} //end case
			case Q1_CONTENTS_WATER:
			{
				brush->side = CONTENTS_WATER;
				return brush;
			} //end case
			case Q1_CONTENTS_SLIME:
			{
				brush->side = CONTENTS_SLIME;
				return brush;
			} //end case
			case Q1_CONTENTS_LAVA:
			{
				brush->side = CONTENTS_LAVA;
				return brush;
			} //end case
#ifdef HLCONTENTS
			//these contents should not be found in the BSP
			case Q1_CONTENTS_ORIGIN:
			case Q1_CONTENTS_CURRENT_0:
			case Q1_CONTENTS_CURRENT_90:
			case Q1_CONTENTS_CURRENT_180:
			case Q1_CONTENTS_CURRENT_270:
			case Q1_CONTENTS_CURRENT_UP:
			case Q1_CONTENTS_CURRENT_DOWN:
			{
				Error("Q1_CreateBrushes_r: found contents %d in Half-Life BSP", leaf->contents);
				return NULL;
			} //end case
#endif HLCONTENTS
			default:
			{
				Error("Q1_CreateBrushes_r: unknown contents %d in Half-Life BSP", leaf->contents);
				return NULL;
			} //end default
		} //end switch
		return NULL;
	} //end if
	//if the rest of the tree is solid
	/*if (Q1_SolidTree_r(nodenum))
	{
		brush->side = CONTENTS_SOLID;
		return brush;
	} //end if*/
	//
	planenum = q1_dnodes[nodenum].planenum;
	planenum = FindFloatPlane(q1_dplanes[planenum].normal, q1_dplanes[planenum].dist);
	//split the brush with the node plane
	Q1_SplitBrush(brush, planenum, nodenum, &front, &back);
	//free the original brush
	FreeBrush(brush);
	//every node must split the brush in two
	if (!front || !back)
	{
		Log_Print("Q1_CreateBrushes_r: WARNING node not splitting brush\n");
		//return NULL;
	} //end if
	//create brushes recursively
	if (front) front = Q1_CreateBrushes_r(front, q1_dnodes[nodenum].children[0]);
	if (back) back = Q1_CreateBrushes_r(back, q1_dnodes[nodenum].children[1]);
	//link the brushes if possible and return them
	if (front)
	{
		for (brush = front; brush->next; brush = brush->next);
		brush->next = back;
		return front;
	} //end if
	else
	{
		return back;
	} //end else
}