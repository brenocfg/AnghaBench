#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numpoints; int** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DotProduct (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int MAX_MAP_BOUNDS ; 
 int ON_EPSILON ; 
 int VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int /*<<< orphan*/ ) ; 
 int WindingArea (TYPE_1__*) ; 
 int /*<<< orphan*/  WindingPlane (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

void CheckWinding (winding_t *w)
{
	int		i, j;
	vec_t	*p1, *p2;
	vec_t	d, edgedist;
	vec3_t	dir, edgenormal, facenormal;
	vec_t	area;
	vec_t	facedist;

	if (w->numpoints < 3)
		Com_Error (ERR_DROP, "CheckWinding: %i points",w->numpoints);
	
	area = WindingArea(w);
	if (area < 1)
		Com_Error (ERR_DROP, "CheckWinding: %f area", area);

	WindingPlane (w, facenormal, &facedist);
	
	for (i=0 ; i<w->numpoints ; i++)
	{
		p1 = w->p[i];

		for (j=0 ; j<3 ; j++)
			if (p1[j] > MAX_MAP_BOUNDS || p1[j] < -MAX_MAP_BOUNDS)
				Com_Error (ERR_DROP, "CheckFace: BUGUS_RANGE: %f",p1[j]);

		j = i+1 == w->numpoints ? 0 : i+1;
		
	// check the point is on the face plane
		d = DotProduct (p1, facenormal) - facedist;
		if (d < -ON_EPSILON || d > ON_EPSILON)
			Com_Error (ERR_DROP, "CheckWinding: point off plane");
	
	// check the edge isnt degenerate
		p2 = w->p[j];
		VectorSubtract (p2, p1, dir);
		
		if (VectorLength (dir) < ON_EPSILON)
			Com_Error (ERR_DROP, "CheckWinding: degenerate edge");
			
		CrossProduct (facenormal, dir, edgenormal);
		VectorNormalize2 (edgenormal, edgenormal);
		edgedist = DotProduct (p1, edgenormal);
		edgedist += ON_EPSILON;
		
	// all other points must be on front side
		for (j=0 ; j<w->numpoints ; j++)
		{
			if (j == i)
				continue;
			d = DotProduct (w->p[j], edgenormal);
			if (d > edgedist)
				Com_Error (ERR_DROP, "CheckWinding: non-convex");
		}
	}
}