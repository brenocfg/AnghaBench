#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; scalar_t__ texinfo; int planenum; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_12__ {int sidefound; TYPE_2__* side; TYPE_1__* onnode; TYPE_5__** nodes; } ;
typedef  TYPE_3__ portal_t ;
struct TYPE_13__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_4__ plane_t ;
struct TYPE_14__ {int contents; TYPE_7__* brushlist; } ;
typedef  TYPE_5__ node_t ;
struct TYPE_15__ {int contents; int numsides; TYPE_2__* original_sides; } ;
typedef  TYPE_6__ mapbrush_t ;
struct TYPE_16__ {TYPE_6__* original; struct TYPE_16__* next; } ;
typedef  TYPE_7__ bspbrush_t ;
struct TYPE_10__ {int planenum; } ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 int SFL_BEVEL ; 
 scalar_t__ TEXINFO_NODE ; 
 int VisibleContents (int) ; 
 TYPE_4__* mapplanes ; 

void FindPortalSide (portal_t *p)
{
	int			viscontents;
	bspbrush_t	*bb;
	mapbrush_t	*brush;
	node_t		*n;
	int			i,j;
	int			planenum;
	side_t		*side, *bestside;
	float		dot, bestdot;
	plane_t		*p1, *p2;

	// decide which content change is strongest
	// solid > lava > water, etc
	viscontents = VisibleContents (p->nodes[0]->contents ^ p->nodes[1]->contents);
	if (!viscontents)
		return;

	planenum = p->onnode->planenum;
	bestside = NULL;
	bestdot = 0;

	for (j=0 ; j<2 ; j++)
	{
		n = p->nodes[j];
		p1 = &mapplanes[p->onnode->planenum];
		for (bb=n->brushlist ; bb ; bb=bb->next)
		{
			brush = bb->original;
			if ( !(brush->contents & viscontents) )
				continue;
			for (i=0 ; i<brush->numsides ; i++)
			{
				side = &brush->original_sides[i];
				if (side->flags & SFL_BEVEL)
					continue;
				if (side->texinfo == TEXINFO_NODE)
					continue;		// non-visible
				if ((side->planenum&~1) == planenum)
				{	// exact match
					bestside = &brush->original_sides[i];
					goto gotit;
				} //end if
				// see how close the match is
				p2 = &mapplanes[side->planenum&~1];
				dot = DotProduct (p1->normal, p2->normal);
				if (dot > bestdot)
				{
					bestdot = dot;
					bestside = side;
				} //end if
			} //end for
		} //end for
	} //end for

gotit:
	if (!bestside)
		Log_Print("WARNING: side not found for portal\n");

	p->sidefound = true;
	p->side = bestside;
}