#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numpoints; float** points; } ;
typedef  TYPE_1__ winding_t ;
typedef  float vec_t ;
typedef  float* vec3_t ;
struct TYPE_8__ {int* normal; float dist; } ;
typedef  TYPE_2__ plane_t ;

/* Variables and functions */
 float DotProduct (float*,int*) ; 
 int MAX_POINTS_ON_FIXED_WINDING ; 
 size_t SIDE_BACK ; 
 int SIDE_CROSS ; 
 size_t SIDE_FRONT ; 
 int SIDE_ON ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  _printf (char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

int VS_ChopWinding (winding_t *in, plane_t *split, float epsilon)
{
	vec_t	dists[128];
	int		sides[128];
	int		counts[3];
	vec_t	dot;
	int		i, j;
	vec_t	*p1, *p2;
	vec3_t	mid;
	winding_t out;
	winding_t	*neww;

	counts[0] = counts[1] = counts[2] = 0;

	// determine sides for each point
	for (i=0 ; i<in->numpoints ; i++)
	{
		dot = DotProduct (in->points[i], split->normal);
		dot -= split->dist;
		dists[i] = dot;
		if (dot > epsilon)
			sides[i] = SIDE_FRONT;
		else if (dot < -epsilon)
			sides[i] = SIDE_BACK;
		else
		{
			sides[i] = SIDE_ON;
		}
		counts[sides[i]]++;
	}

	if (!counts[SIDE_BACK])
	{
		if (!counts[SIDE_FRONT])
			return SIDE_ON;
		else
			return SIDE_FRONT;
	}
	
	if (!counts[SIDE_FRONT])
	{
		return SIDE_BACK;
	}

	sides[i] = sides[0];
	dists[i] = dists[0];
	
	neww = &out;

	neww->numpoints = 0;

	for (i=0 ; i<in->numpoints ; i++)
	{
		p1 = in->points[i];

		if (neww->numpoints >= MAX_POINTS_ON_FIXED_WINDING)
		{
			_printf("WARNING: VS_ChopWinding -> MAX_POINTS_ON_FIXED_WINDING overflowed\n");
			return SIDE_FRONT;		// can't chop -- fall back to original
		}

		if (sides[i] == SIDE_ON)
		{
			VectorCopy (p1, neww->points[neww->numpoints]);
			neww->numpoints++;
			continue;
		}
	
		if (sides[i] == SIDE_FRONT)
		{
			VectorCopy (p1, neww->points[neww->numpoints]);
			neww->numpoints++;
		}
		
		if (sides[i+1] == SIDE_ON || sides[i+1] == sides[i])
			continue;
			
		if (neww->numpoints >= MAX_POINTS_ON_FIXED_WINDING)
		{
			_printf("WARNING: VS_ChopWinding -> MAX_POINTS_ON_FIXED_WINDING overflowed\n");
			return SIDE_FRONT;		// can't chop -- fall back to original
		}

		// generate a split point
		p2 = in->points[(i+1)%in->numpoints];
		
		dot = dists[i] / (dists[i]-dists[i+1]);
		for (j=0 ; j<3 ; j++)
		{	// avoid round off error when possible
			if (split->normal[j] == 1)
				mid[j] = split->dist;
			else if (split->normal[j] == -1)
				mid[j] = -split->dist;
			else
				mid[j] = p1[j] + dot*(p2[j]-p1[j]);
		}
			
		VectorCopy (mid, neww->points[neww->numpoints]);
		neww->numpoints++;
	}
	memcpy(in, &out, sizeof(winding_t));
	
	return SIDE_CROSS;
}