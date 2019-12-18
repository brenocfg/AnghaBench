#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_10__ {scalar_t__* maxs; scalar_t__* mins; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_9__ {int planenum; int /*<<< orphan*/  flags; int /*<<< orphan*/  texinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBrush (TYPE_2__*) ; 
 int /*<<< orphan*/  SFL_VISIBLE ; 
 int /*<<< orphan*/  SplitBrush (TYPE_2__*,int,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/  TEXINFO_NODE ; 
 int* maxplanenums ; 
 int* minplanenums ; 

bspbrush_t *ClipBrushToBox(bspbrush_t *brush, vec3_t clipmins, vec3_t clipmaxs)
{
	int		i, j;
	bspbrush_t	*front,	*back;
	int		p;

	for (j=0 ; j<2 ; j++)
	{
		if (brush->maxs[j] > clipmaxs[j])
		{
			SplitBrush (brush, maxplanenums[j], &front, &back);
			if (front)
				FreeBrush (front);
			brush = back;
			if (!brush)
				return NULL;
		}
		if (brush->mins[j] < clipmins[j])
		{
			SplitBrush (brush, minplanenums[j], &front, &back);
			if (back)
				FreeBrush (back);
			brush = front;
			if (!brush)
				return NULL;
		}
	}

	// remove any colinear faces

	for (i=0 ; i<brush->numsides ; i++)
	{
		p = brush->sides[i].planenum & ~1;
		if (p == maxplanenums[0] || p == maxplanenums[1] 
			|| p == minplanenums[0] || p == minplanenums[1])
		{
			brush->sides[i].texinfo = TEXINFO_NODE;
			brush->sides[i].flags &= ~SFL_VISIBLE;
		}
	}
	return brush;
}