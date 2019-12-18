#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_12__ {double* filter; double hitFraction; int* hit; int /*<<< orphan*/  passSolid; } ;
typedef  TYPE_1__ trace_t ;
struct TYPE_13__ {int numOpenLeafs; size_t* openLeafNumbers; int /*<<< orphan*/  patchshadows; TYPE_1__* trace; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_14__ {scalar_t__ patch; } ;
typedef  TYPE_3__ surfaceTest_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_15__ {int numLeafSurfaces; int firstLeafSurface; } ;
typedef  TYPE_4__ dleaf_t ;
typedef  int byte ;

/* Variables and functions */
 int MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/  TraceAgainstSurface (TYPE_2__*,TYPE_3__*) ; 
 int TraceLine_r (int /*<<< orphan*/ ,int* const,int* const,TYPE_2__*) ; 
 int /*<<< orphan*/  VectorCopy (int* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_totalTrace ; 
 TYPE_4__* dleafs ; 
 int* dleafsurfaces ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ noSurfaces ; 
 int numDrawSurfaces ; 
 int numthreads ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_3__** surfaceTest ; 

void TraceLine( const vec3_t start, const vec3_t stop, trace_t *trace, qboolean testAll, traceWork_t *tw ) {
	int				r;
	int				i, j;
	dleaf_t			*leaf;
	float			oldHitFrac;
	surfaceTest_t	*test;
	int				surfaceNum;
	byte			surfaceTested[MAX_MAP_DRAW_SURFS/8];
	;

	if ( numthreads == 1 ) {
		c_totalTrace++;
	}

	// assume all light gets through, unless the ray crosses
	// a translucent surface
	trace->filter[0] = 1.0;
	trace->filter[1] = 1.0;
	trace->filter[2] = 1.0;

	VectorCopy( start, tw->start );
	VectorCopy( stop, tw->end );
	tw->trace = trace;

	tw->numOpenLeafs = 0;

	trace->passSolid = qfalse;
	trace->hitFraction = 1.0;

	r = TraceLine_r( 0, start, stop, tw );

	// if we hit a solid leaf, stop without testing the leaf
	// surfaces.  Note that the plane and endpoint might not
	// be the first solid intersection along the ray.
	if ( r && !testAll ) {
		return;
	}

	if ( noSurfaces ) {
		return;
	}

	memset( surfaceTested, 0, (numDrawSurfaces+7)/8 );
	oldHitFrac = trace->hitFraction;

	for ( i = 0 ; i < tw->numOpenLeafs ; i++ ) {
		leaf = &dleafs[ tw->openLeafNumbers[ i ] ];
		for ( j = 0 ; j < leaf->numLeafSurfaces ; j++ ) {
			surfaceNum = dleafsurfaces[ leaf->firstLeafSurface + j ];

			// make sure we don't test the same ray against a surface more than once
			if ( surfaceTested[ surfaceNum>>3 ] & ( 1 << ( surfaceNum & 7) ) ) {
				continue;
			}
			surfaceTested[ surfaceNum>>3 ] |= ( 1 << ( surfaceNum & 7 ) );

			test = surfaceTest[ surfaceNum ];
			if ( !test ) {
				continue;
			}
			//
			if ( !tw->patchshadows && test->patch ) {
				continue;
			}
			TraceAgainstSurface( tw, test );
		}

		// if the trace is now solid, we can't possibly hit anything closer
		if ( trace->hitFraction < oldHitFrac ) {
			trace->passSolid = qtrue;
			break;
		}
	}
	
	for ( i = 0 ; i < 3 ; i++ ) {
		trace->hit[i] = start[i] + ( stop[i] - start[i] ) * trace->hitFraction;
	}
}