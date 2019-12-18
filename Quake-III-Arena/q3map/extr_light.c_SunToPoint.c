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
typedef  int* vec3_t ;
struct TYPE_5__ {scalar_t__* hit; int* filter; } ;
typedef  TYPE_1__ trace_t ;
typedef  int /*<<< orphan*/  traceWork_t ;
struct TYPE_6__ {scalar_t__** bounds; } ;
typedef  TYPE_2__ skyBrush_t ;

/* Variables and functions */
 int MAX_WORLD_COORD ; 
 int /*<<< orphan*/  TraceLine (int* const,int*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int /*<<< orphan*/  VectorMA (int* const,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  c_sunHit ; 
 int /*<<< orphan*/  c_sunMiss ; 
 int numSkyBrushes ; 
 int numthreads ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_2__* skyBrushes ; 
 int /*<<< orphan*/  sunDirection ; 
 int* sunLight ; 

void SunToPoint( const vec3_t origin, traceWork_t *tw, vec3_t addLight ) {
	int			i;
	trace_t		trace;
	skyBrush_t	*b;
	vec3_t		end;

	if ( !numSkyBrushes ) {
		VectorClear( addLight );
		return;
	}

	VectorMA( origin, MAX_WORLD_COORD * 2, sunDirection, end );

	TraceLine( origin, end, &trace, qtrue, tw );

	// see if trace.hit is inside a sky brush
	for ( i = 0 ; i < numSkyBrushes ; i++) {
		b = &skyBrushes[ i ];

		// this assumes that sky brushes are axial...
		if (   trace.hit[0] < b->bounds[0][0] 
			|| trace.hit[0] > b->bounds[1][0]
			|| trace.hit[1] < b->bounds[0][1]
			|| trace.hit[1] > b->bounds[1][1]
			|| trace.hit[2] < b->bounds[0][2]
			|| trace.hit[2] > b->bounds[1][2] ) {
			continue;
		}


		// trace again to get intermediate filters
		TraceLine( origin, trace.hit, &trace, qtrue, tw );

		// we hit the sky, so add sunlight
		if ( numthreads == 1 ) {
			c_sunHit++;
		}
		addLight[0] = trace.filter[0] * sunLight[0];
		addLight[1] = trace.filter[1] * sunLight[1];
		addLight[2] = trace.filter[2] * sunLight[2];

		return;
	}

	if ( numthreads == 1 ) {
		c_sunMiss++;
	}

	VectorClear( addLight );
}