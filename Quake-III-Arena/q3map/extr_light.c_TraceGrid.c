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
typedef  scalar_t__* vec3_t ;
typedef  int /*<<< orphan*/  traceWork_t ;
struct TYPE_5__ {int /*<<< orphan*/  origin; struct TYPE_5__* next; } ;
typedef  TYPE_1__ light_t ;
struct TYPE_6__ {scalar_t__* color; scalar_t__* dir; } ;
typedef  TYPE_2__ contribution_t ;

/* Variables and functions */
 int /*<<< orphan*/  ColorToBytes (scalar_t__*,scalar_t__*) ; 
 float DotProduct (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  LightContributionToPoint (TYPE_1__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int MAX_CONTRIBUTIONS ; 
 int /*<<< orphan*/  NormalToLatLong (scalar_t__*,scalar_t__*) ; 
 scalar_t__ PointInSolid (scalar_t__*) ; 
 int /*<<< orphan*/  SunToPoint (scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  VectorClear (scalar_t__*) ; 
 int /*<<< orphan*/  VectorCopy (scalar_t__*,scalar_t__*) ; 
 float VectorLength (scalar_t__*) ; 
 int /*<<< orphan*/  VectorMA (scalar_t__*,double,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorNormalize (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__* ambientColor ; 
 int* gridBounds ; 
 scalar_t__* gridData ; 
 scalar_t__* gridMins ; 
 int* gridSize ; 
 TYPE_1__* lights ; 
 scalar_t__* sunDirection ; 

void TraceGrid( int num ) {
	int			x, y, z;
	vec3_t		origin;
	light_t		*light;
	vec3_t		color;
	int			mod;
	vec3_t		directedColor;
	vec3_t		summedDir;
	contribution_t	contributions[MAX_CONTRIBUTIONS];
	int			numCon;
	int			i;
	traceWork_t	tw;
	float		addSize;

	mod = num;
	z = mod / ( gridBounds[0] * gridBounds[1] );
	mod -= z * ( gridBounds[0] * gridBounds[1] );

	y = mod / gridBounds[0];
	mod -= y * gridBounds[0];

	x = mod;

	origin[0] = gridMins[0] + x * gridSize[0];
	origin[1] = gridMins[1] + y * gridSize[1];
	origin[2] = gridMins[2] + z * gridSize[2];

	if ( PointInSolid( origin ) ) {
		vec3_t	baseOrigin;
		int		step;

		VectorCopy( origin, baseOrigin );

		// try to nudge the origin around to find a valid point
		for ( step = 9 ; step <= 18 ; step += 9 ) {
			for ( i = 0 ; i < 8 ; i++ ) {
				VectorCopy( baseOrigin, origin );
				if ( i & 1 ) {
					origin[0] += step;
				} else {
					origin[0] -= step;
				}
				if ( i & 2 ) {
					origin[1] += step;
				} else {
					origin[1] -= step;
				}
				if ( i & 4 ) {
					origin[2] += step;
				} else {
					origin[2] -= step;
				}

				if ( !PointInSolid( origin ) ) {
					break;
				}
			}
			if ( i != 8 ) {
				break;
			}
		}
		if ( step > 18 ) {
			// can't find a valid point at all
			for ( i = 0 ; i < 8 ; i++ ) {
				gridData[ num*8 + i ] = 0;
			}
			return;
		}
	}

	VectorClear( summedDir );

	// trace to all the lights

	// find the major light direction, and divide the
	// total light between that along the direction and
	// the remaining in the ambient 
	numCon = 0;
	for ( light = lights ; light ; light = light->next ) {
		vec3_t		add;
		vec3_t		dir;
		float		addSize;

		if ( !LightContributionToPoint( light, origin, add, &tw ) ) {
			continue;
		}

		VectorSubtract( light->origin, origin, dir );
		VectorNormalize( dir, dir );

		VectorCopy( add, contributions[numCon].color );
		VectorCopy( dir, contributions[numCon].dir );
		numCon++;

		addSize = VectorLength( add );
		VectorMA( summedDir, addSize, dir, summedDir );

		if ( numCon == MAX_CONTRIBUTIONS-1 ) {
			break;
		}
	}

	//
	// trace directly to the sun
	//
	SunToPoint( origin, &tw, color );
	addSize = VectorLength( color );
	if ( addSize > 0 ) {
		VectorCopy( color, contributions[numCon].color );
		VectorCopy( sunDirection, contributions[numCon].dir );
		VectorMA( summedDir, addSize, sunDirection, summedDir );
		numCon++;
	}


	// now that we have identified the primary light direction,
	// go back and seperate all the light into directed and ambient
	VectorNormalize( summedDir, summedDir );
	VectorCopy( ambientColor, color );
	VectorClear( directedColor );

	for ( i = 0 ; i < numCon ; i++ ) {
		float	d;

		d = DotProduct( contributions[i].dir, summedDir );
		if ( d < 0 ) {
			d = 0;
		}

		VectorMA( directedColor, d, contributions[i].color, directedColor );

		// the ambient light will be at 1/4 the value of directed light
		d = 0.25 * ( 1.0 - d );
		VectorMA( color, d, contributions[i].color, color );
	}

	// now do some fudging to keep the ambient from being too low
	VectorMA( color, 0.25, directedColor, color );

	//
	// save the resulting value out
	//
	ColorToBytes( color, gridData + num*8 );
	ColorToBytes( directedColor, gridData + num*8 + 3 );

	VectorNormalize( summedDir, summedDir );
	NormalToLatLong( summedDir, gridData + num*8 + 6);
}