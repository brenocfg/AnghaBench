#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_2__ winding_t ;
typedef  double vec_t ;
typedef  int qboolean ;
struct TYPE_10__ {int type; float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;
struct TYPE_11__ {float* mins; float* maxs; int numsides; TYPE_1__* sides; } ;
typedef  TYPE_4__ bspbrush_t ;
struct TYPE_8__ {int planenum; int flags; scalar_t__ texinfo; int surf; TYPE_2__* winding; } ;

/* Variables and functions */
 int BoxOnPlaneSide (float*,float*,TYPE_3__*) ; 
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAPFILE_PLANES ; 
 float PLANESIDE_EPSILON ; 
 int PSIDE_BACK ; 
 int PSIDE_BOTH ; 
 int PSIDE_FACING ; 
 int PSIDE_FRONT ; 
 int SFL_TESTED ; 
 int SFL_VISIBLE ; 
 int SURF_HINT ; 
 int SURF_SKIP ; 
 scalar_t__ TEXINFO_NODE ; 
 TYPE_3__* mapplanes ; 

int TestBrushToPlanenum (bspbrush_t *brush, int planenum,
						 int *numsplits, qboolean *hintsplit, int *epsilonbrush)
{
	int i, j, num;
	plane_t *plane;
	int s = 0;
	winding_t *w;
	vec_t d, d_front, d_back;
	int front, back;
	int type;
	float dist;

	*numsplits = 0;
	*hintsplit = false;

	plane = &mapplanes[planenum];

#ifdef ME
	//fast axial cases
	type = plane->type;
	if (type < 3)
	{
		dist = plane->dist;
		if (dist + PLANESIDE_EPSILON < brush->mins[type]) return PSIDE_FRONT;
		if (dist - PLANESIDE_EPSILON > brush->maxs[type]) return PSIDE_BACK;
		if (brush->mins[type] < dist - PLANESIDE_EPSILON &&
					brush->maxs[type] > dist + PLANESIDE_EPSILON) s = PSIDE_BOTH;
	} //end if

	if (s != PSIDE_BOTH)
#endif //ME
	{
		// if the brush actually uses the planenum,
		// we can tell the side for sure
		for (i = 0; i < brush->numsides; i++)
		{
			num = brush->sides[i].planenum;
			if (num >= MAX_MAPFILE_PLANES) Error ("bad planenum");
			if (num == planenum)
			{
				//we don't need to test this side plane again
				brush->sides[i].flags |= SFL_TESTED;
				return PSIDE_BACK|PSIDE_FACING;
			} //end if
			if (num == (planenum ^ 1) )
			{
				//we don't need to test this side plane again
				brush->sides[i].flags |= SFL_TESTED;
				return PSIDE_FRONT|PSIDE_FACING;
			} //end if
		} //end for

		// box on plane side
		s = BoxOnPlaneSide (brush->mins, brush->maxs, plane);

		if (s != PSIDE_BOTH) return s;
	} //end if

	// if both sides, count the visible faces split
	d_front = d_back = 0;

	for (i = 0; i < brush->numsides; i++)
	{
		if (brush->sides[i].texinfo == TEXINFO_NODE)
			continue;		// on node, don't worry about splits
		if (!(brush->sides[i].flags & SFL_VISIBLE))
			continue;		// we don't care about non-visible
		w = brush->sides[i].winding;
		if (!w) continue;
		front = back = 0;
		for (j = 0; j < w->numpoints; j++)
		{
			d = DotProduct(w->p[j], plane->normal) - plane->dist;
			if (d > d_front) d_front = d;
			if (d < d_back) d_back = d;
			if (d > 0.1) // PLANESIDE_EPSILON)
				front = 1;
			if (d < -0.1) // PLANESIDE_EPSILON)
				back = 1;
		} //end for
		if (front && back)
		{
			if ( !(brush->sides[i].surf & SURF_SKIP) )
			{
				(*numsplits)++;
				if (brush->sides[i].surf & SURF_HINT)
				{
					*hintsplit = true;
				} //end if
			} //end if
		} //end if
	} //end for

	if ( (d_front > 0.0 && d_front < 1.0)
		|| (d_back < 0.0 && d_back > -1.0) )
		(*epsilonbrush)++;

#if 0
	if (*numsplits == 0)
	{	//	didn't really need to be split
		if (front) s = PSIDE_FRONT;
		else if (back) s = PSIDE_BACK;
		else s = 0;
	}
#endif

	return s;
}