#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int* vec3_t ;
struct TYPE_8__ {size_t planenum; void* bevel; int /*<<< orphan*/  contents; TYPE_1__* winding; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_10__ {int numsides; float* maxs; float* mins; TYPE_2__* sides; } ;
struct TYPE_9__ {int* normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int*,int*,int*) ; 
 float DotProduct (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Error (char*) ; 
 void* FindFloatPlane (int*,float) ; 
 int MAX_BUILD_SIDES ; 
 scalar_t__ PlaneEqual (TYPE_4__*,int*,float) ; 
 int /*<<< orphan*/  SnapVector (int*) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 double VectorNormalize (int*,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 TYPE_5__* buildBrush ; 
 int /*<<< orphan*/  c_boxbevels ; 
 int /*<<< orphan*/  c_edgebevels ; 
 TYPE_4__* mapplanes ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 void* qtrue ; 

void AddBrushBevels( void ) {
	int		axis, dir;
	int		i, order;
	side_t	sidetemp;
	side_t	*s;
	vec3_t	normal;
	float	dist;

	//
	// add the axial planes
	//
	order = 0;
	for (axis=0 ; axis <3 ; axis++)
	{
		for (dir=-1 ; dir <= 1 ; dir+=2, order++)
		{
			// see if the plane is allready present
			for ( i=0, s=buildBrush->sides ; i < buildBrush->numsides ; i++,s++ ) {
				if (mapplanes[s->planenum].normal[axis] == dir)
					break;
			}

			if (i == buildBrush->numsides )
			{	// add a new side
				if ( buildBrush->numsides == MAX_BUILD_SIDES ) {
					Error( "MAX_BUILD_SIDES" );
				}
				memset( s, 0, sizeof( *s ) );
				buildBrush->numsides++;
				VectorClear (normal);
				normal[axis] = dir;
				if (dir == 1)
					dist = buildBrush->maxs[axis];
				else
					dist = -buildBrush->mins[axis];
				s->planenum = FindFloatPlane (normal, dist);
				s->contents = buildBrush->sides[0].contents;
				s->bevel = qtrue;
				c_boxbevels++;
			}

			// if the plane is not in it canonical order, swap it
			if (i != order)
			{
				sidetemp = buildBrush->sides[order];
				buildBrush->sides[order] = buildBrush->sides[i];
				buildBrush->sides[i] = sidetemp;
			}
		}
	}

	//
	// add the edge bevels
	//
	if ( buildBrush->numsides == 6 ) {
		return;		// pure axial
  } else {
	  int			j, k, l;
	  float		d;
	  winding_t	*w, *w2;
	  side_t		*s2;
	  vec3_t		vec, vec2;

	  // test the non-axial plane edges
	  // this code tends to cause some problems...
	  for (i=6 ; i<buildBrush->numsides ; i++)
	  {
		  s = buildBrush->sides + i;
		  w = s->winding;
		  if (!w)
			  continue;
		  for (j=0 ; j<w->numpoints ; j++)
		  {
			  k = (j+1)%w->numpoints;
			  VectorSubtract (w->p[j], w->p[k], vec);
			  if (VectorNormalize (vec, vec) < 0.5)
				  continue;
			  SnapVector (vec);
			  for (k=0 ; k<3 ; k++)
				  if ( vec[k] == -1 || vec[k] == 1)
					  break;	// axial
			  if (k != 3)
				  continue;	// only test non-axial edges

			  // try the six possible slanted axials from this edge
			  for (axis=0 ; axis <3 ; axis++)
			  {
				  for (dir=-1 ; dir <= 1 ; dir+=2)
				  {
					  // construct a plane
					  VectorClear (vec2);
					  vec2[axis] = dir;
					  CrossProduct (vec, vec2, normal);
					  if (VectorNormalize (normal, normal) < 0.5)
						  continue;
					  dist = DotProduct (w->p[j], normal);

					  // if all the points on all the sides are
					  // behind this plane, it is a proper edge bevel
					  for (k=0 ; k < buildBrush->numsides ; k++)
					  {
						  // if this plane has allready been used, skip it
						  if (PlaneEqual (&mapplanes[buildBrush->sides[k].planenum]
							  , normal, dist) )
							  break;

						  w2 = buildBrush->sides[k].winding;
						  if (!w2)
							  continue;
						  for (l=0 ; l<w2->numpoints ; l++)
						  {
							  d = DotProduct (w2->p[l], normal) - dist;
							  if (d > 0.1)
								  break;	// point in front
						  }
						  if (l != w2->numpoints)
							  break;
					  }

					  if (k != buildBrush->numsides)
						  continue;	// wasn't part of the outer hull
					  // add this plane
					  if ( buildBrush->numsides == MAX_BUILD_SIDES ) {
						  Error( "MAX_BUILD_SIDES" );
					  }

					  s2 = &buildBrush->sides[buildBrush->numsides];
					  buildBrush->numsides++;
					  memset( s2, 0, sizeof( *s2 ) );

					  s2->planenum = FindFloatPlane (normal, dist);
					  s2->contents = buildBrush->sides[0].contents;
					  s2->bevel = qtrue;
					  c_edgebevels++;
				  }
			  }
		  }
	  }
  }
}