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
struct TYPE_5__ {int planenum; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_6__ {scalar_t__ entitynum; int numsides; TYPE_1__* original_sides; } ;
typedef  TYPE_2__ mapbrush_t ;

/* Variables and functions */
 TYPE_2__* mapbrushes ; 
 int nummapbrushes ; 

int BrushExists(mapbrush_t *brush)
{
	int i, s1, s2;
	side_t *side1, *side2;
	mapbrush_t *brush1, *brush2;

	for (i = 0; i < nummapbrushes; i++)
	{
		brush1 = brush;
		brush2 = &mapbrushes[i];
		//compare the brushes
		if (brush1->entitynum != brush2->entitynum) continue;
		//if (brush1->contents != brush2->contents) continue;
		if (brush1->numsides != brush2->numsides) continue;
		for (s1 = 0; s1 < brush1->numsides; s1++)
		{
			side1 = brush1->original_sides + s1;
			//
			for (s2 = 0; s2 < brush2->numsides; s2++)
			{
				side2 = brush2->original_sides + s2;
				//
				if ((side1->planenum & ~1) == (side2->planenum & ~1)
//						&& side1->texinfo == side2->texinfo
//						&& side1->contents == side2->contents
//						&& side1->surf == side2->surf
					) break;
			} //end if
			if (s2 >= brush2->numsides) break;
		} //end for
		if (s1 >= brush1->numsides) return true;
	} //end for
	return false;
}