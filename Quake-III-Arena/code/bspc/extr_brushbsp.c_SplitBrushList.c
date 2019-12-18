#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_14__ {int planenum; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_15__ {int side; int numsides; struct TYPE_15__* next; TYPE_1__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;

/* Variables and functions */
 TYPE_3__* CopyBrush (TYPE_3__*) ; 
 int PSIDE_BACK ; 
 int PSIDE_BOTH ; 
 int PSIDE_FACING ; 
 int PSIDE_FRONT ; 
 int /*<<< orphan*/  SplitBrush (TYPE_3__*,int,TYPE_3__**,TYPE_3__**) ; 
 int /*<<< orphan*/  TEXINFO_NODE ; 

void SplitBrushList (bspbrush_t *brushes, 
	node_t *node, bspbrush_t **front, bspbrush_t **back)
{
	bspbrush_t	*brush, *newbrush, *newbrush2;
	side_t		*side;
	int			sides;
	int			i;

	*front = *back = NULL;

	for (brush = brushes; brush; brush = brush->next)
	{
		sides = brush->side;

		if (sides == PSIDE_BOTH)
		{	// split into two brushes
			SplitBrush (brush, node->planenum, &newbrush, &newbrush2);
			if (newbrush)
			{
				newbrush->next = *front;
				*front = newbrush;
			} //end if
			if (newbrush2)
			{
				newbrush2->next = *back;
				*back = newbrush2;
			} //end if
			continue;
		} //end if

		newbrush = CopyBrush (brush);

		// if the planenum is actualy a part of the brush
		// find the plane and flag it as used so it won't be tried
		// as a splitter again
		if (sides & PSIDE_FACING)
		{
			for (i=0 ; i<newbrush->numsides ; i++)
			{
				side = newbrush->sides + i;
				if ( (side->planenum& ~1) == node->planenum)
					side->texinfo = TEXINFO_NODE;
			} //end for
		} //end if
		if (sides & PSIDE_FRONT)
		{
			newbrush->next = *front;
			*front = newbrush;
			continue;
		} //end if
		if (sides & PSIDE_BACK)
		{
			newbrush->next = *back;
			*back = newbrush;
			continue;
		} //end if
	} //end for
}