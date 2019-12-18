#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {size_t planenum; int /*<<< orphan*/ * winding; scalar_t__ backSide; scalar_t__ bevel; } ;
typedef  TYPE_1__ side_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_3__ bspbrush_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BaseWindingForPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BoundBrush (TYPE_3__*) ; 
 int /*<<< orphan*/  ChopWindingInPlace (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 TYPE_2__* mapplanes ; 

qboolean CreateBrushWindings (bspbrush_t *brush)
{
	int			i, j;
	winding_t	*w;
	side_t		*side;
	plane_t		*plane;

	for ( i = 0; i < brush->numsides; i++ )
	{
		side = &brush->sides[i];
		// don't create a winding for a bevel
		if ( side->bevel ) {
			continue;
		}
		plane = &mapplanes[side->planenum];
		w = BaseWindingForPlane (plane->normal, plane->dist);
		for ( j = 0; j < brush->numsides && w; j++ )
		{
			if (i == j)
				continue;
			if ( brush->sides[j].planenum == ( brush->sides[i].planenum ^ 1 ) )
				continue;		// back side clipaway
			if (brush->sides[j].bevel)
				continue;
			if (brush->sides[j].backSide)
				continue;
			plane = &mapplanes[brush->sides[j].planenum^1];
			ChopWindingInPlace (&w, plane->normal, plane->dist, 0); //CLIP_EPSILON);
		}
		// free any existing winding
		if ( side->winding ) {
			FreeWinding( side->winding );
		}
		side->winding = w;
	}

	return BoundBrush (brush);
}