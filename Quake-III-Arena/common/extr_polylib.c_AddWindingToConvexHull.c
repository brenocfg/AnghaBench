#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int numpoints; float** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  float* vec3_t ;
typedef  scalar_t__ qboolean ;

/* Variables and functions */
 TYPE_1__* AllocWinding (int) ; 
 TYPE_1__* CopyWinding (TYPE_1__*) ; 
 int /*<<< orphan*/  CrossProduct (float*,float*,float*) ; 
 float DotProduct (float*,float*) ; 
 int /*<<< orphan*/  FreeWinding (TYPE_1__*) ; 
 int MAX_HULL_POINTS ; 
 float ON_EPSILON ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 int /*<<< orphan*/  VectorNormalize (float*,float*) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,float*) ; 
 int /*<<< orphan*/  memcpy (float**,float**,int) ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 

void	AddWindingToConvexHull( winding_t *w, winding_t **hull, vec3_t normal ) {
	int			i, j, k;
	float		*p, *copy;
	vec3_t		dir;
	float		d;
	int			numHullPoints, numNew;
	vec3_t		hullPoints[MAX_HULL_POINTS];
	vec3_t		newHullPoints[MAX_HULL_POINTS];
	vec3_t		hullDirs[MAX_HULL_POINTS];
	qboolean	hullSide[MAX_HULL_POINTS];
	qboolean	outside;

	if ( !*hull ) {
		*hull = CopyWinding( w );
		return;
	}

	numHullPoints = (*hull)->numpoints;
	memcpy( hullPoints, (*hull)->p, numHullPoints * sizeof(vec3_t) );

	for ( i = 0 ; i < w->numpoints ; i++ ) {
		p = w->p[i];

		// calculate hull side vectors
		for ( j = 0 ; j < numHullPoints ; j++ ) {
			k = ( j + 1 ) % numHullPoints;

			VectorSubtract( hullPoints[k], hullPoints[j], dir );
			VectorNormalize( dir, dir );
			CrossProduct( normal, dir, hullDirs[j] );
		}

		outside = qfalse;
		for ( j = 0 ; j < numHullPoints ; j++ ) {
			VectorSubtract( p, hullPoints[j], dir );
			d = DotProduct( dir, hullDirs[j] );
			if ( d >= ON_EPSILON ) {
				outside = qtrue;
			}
			if ( d >= -ON_EPSILON ) {
				hullSide[j] = qtrue;
			} else {
				hullSide[j] = qfalse;
			}
		}

		// if the point is effectively inside, do nothing
		if ( !outside ) {
			continue;
		}

		// find the back side to front side transition
		for ( j = 0 ; j < numHullPoints ; j++ ) {
			if ( !hullSide[ j % numHullPoints ] && hullSide[ (j + 1) % numHullPoints ] ) {
				break;
			}
		}
		if ( j == numHullPoints ) {
			continue;
		}

		// insert the point here
		VectorCopy( p, newHullPoints[0] );
		numNew = 1;

		// copy over all points that aren't double fronts
		j = (j+1)%numHullPoints;
		for ( k = 0 ; k < numHullPoints ; k++ ) {
			if ( hullSide[ (j+k) % numHullPoints ] && hullSide[ (j+k+1) % numHullPoints ] ) {
				continue;
			}
			copy = hullPoints[ (j+k+1) % numHullPoints ];
			VectorCopy( copy, newHullPoints[numNew] );
			numNew++;
		}

		numHullPoints = numNew;
		memcpy( hullPoints, newHullPoints, numHullPoints * sizeof(vec3_t) );
	}

	FreeWinding( *hull );
	w = AllocWinding( numHullPoints );
	w->numpoints = numHullPoints;
	*hull = w;
	memcpy( w->p, hullPoints, numHullPoints * sizeof(vec3_t) );
}