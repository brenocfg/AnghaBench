#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {float dist; size_t signbits; int /*<<< orphan*/  normal; } ;
struct TYPE_10__ {float fraction; int /*<<< orphan*/  contents; int /*<<< orphan*/  surfaceFlags; TYPE_4__ plane; void* allsolid; void* startsolid; } ;
struct TYPE_9__ {float radius; int /*<<< orphan*/  offset; scalar_t__ use; } ;
struct TYPE_11__ {TYPE_2__ trace; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/ * offsets; TYPE_1__ sphere; } ;
typedef  TYPE_3__ traceWork_t ;
typedef  void* qboolean ;
typedef  TYPE_4__ cplane_t ;
struct TYPE_13__ {int /*<<< orphan*/  surfaceFlags; TYPE_4__* plane; } ;
typedef  TYPE_5__ cbrushside_t ;
struct TYPE_14__ {int numsides; int /*<<< orphan*/  contents; TYPE_5__* sides; } ;
typedef  TYPE_6__ cbrush_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float SURFACE_CLIP_EPSILON ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_brush_traces ; 
 void* qfalse ; 
 void* qtrue ; 

void CM_TraceThroughBrush( traceWork_t *tw, cbrush_t *brush ) {
	int			i;
	cplane_t	*plane, *clipplane;
	float		dist;
	float		enterFrac, leaveFrac;
	float		d1, d2;
	qboolean	getout, startout;
	float		f;
	cbrushside_t	*side, *leadside;
	float		t;
	vec3_t		startp;
	vec3_t		endp;

	enterFrac = -1.0;
	leaveFrac = 1.0;
	clipplane = NULL;

	if ( !brush->numsides ) {
		return;
	}

	c_brush_traces++;

	getout = qfalse;
	startout = qfalse;

	leadside = NULL;

	if ( tw->sphere.use ) {
		//
		// compare the trace against all planes of the brush
		// find the latest time the trace crosses a plane towards the interior
		// and the earliest time the trace crosses a plane towards the exterior
		//
		for (i = 0; i < brush->numsides; i++) {
			side = brush->sides + i;
			plane = side->plane;

			// adjust the plane distance apropriately for radius
			dist = plane->dist + tw->sphere.radius;

			// find the closest point on the capsule to the plane
			t = DotProduct( plane->normal, tw->sphere.offset );
			if ( t > 0 )
			{
				VectorSubtract( tw->start, tw->sphere.offset, startp );
				VectorSubtract( tw->end, tw->sphere.offset, endp );
			}
			else
			{
				VectorAdd( tw->start, tw->sphere.offset, startp );
				VectorAdd( tw->end, tw->sphere.offset, endp );
			}

			d1 = DotProduct( startp, plane->normal ) - dist;
			d2 = DotProduct( endp, plane->normal ) - dist;

			if (d2 > 0) {
				getout = qtrue;	// endpoint is not in solid
			}
			if (d1 > 0) {
				startout = qtrue;
			}

			// if completely in front of face, no intersection with the entire brush
			if (d1 > 0 && ( d2 >= SURFACE_CLIP_EPSILON || d2 >= d1 )  ) {
				return;
			}

			// if it doesn't cross the plane, the plane isn't relevent
			if (d1 <= 0 && d2 <= 0 ) {
				continue;
			}

			// crosses face
			if (d1 > d2) {	// enter
				f = (d1-SURFACE_CLIP_EPSILON) / (d1-d2);
				if ( f < 0 ) {
					f = 0;
				}
				if (f > enterFrac) {
					enterFrac = f;
					clipplane = plane;
					leadside = side;
				}
			} else {	// leave
				f = (d1+SURFACE_CLIP_EPSILON) / (d1-d2);
				if ( f > 1 ) {
					f = 1;
				}
				if (f < leaveFrac) {
					leaveFrac = f;
				}
			}
		}
	} else {
		//
		// compare the trace against all planes of the brush
		// find the latest time the trace crosses a plane towards the interior
		// and the earliest time the trace crosses a plane towards the exterior
		//
		for (i = 0; i < brush->numsides; i++) {
			side = brush->sides + i;
			plane = side->plane;

			// adjust the plane distance apropriately for mins/maxs
			dist = plane->dist - DotProduct( tw->offsets[ plane->signbits ], plane->normal );

			d1 = DotProduct( tw->start, plane->normal ) - dist;
			d2 = DotProduct( tw->end, plane->normal ) - dist;

			if (d2 > 0) {
				getout = qtrue;	// endpoint is not in solid
			}
			if (d1 > 0) {
				startout = qtrue;
			}

			// if completely in front of face, no intersection with the entire brush
			if (d1 > 0 && ( d2 >= SURFACE_CLIP_EPSILON || d2 >= d1 )  ) {
				return;
			}

			// if it doesn't cross the plane, the plane isn't relevent
			if (d1 <= 0 && d2 <= 0 ) {
				continue;
			}

			// crosses face
			if (d1 > d2) {	// enter
				f = (d1-SURFACE_CLIP_EPSILON) / (d1-d2);
				if ( f < 0 ) {
					f = 0;
				}
				if (f > enterFrac) {
					enterFrac = f;
					clipplane = plane;
					leadside = side;
				}
			} else {	// leave
				f = (d1+SURFACE_CLIP_EPSILON) / (d1-d2);
				if ( f > 1 ) {
					f = 1;
				}
				if (f < leaveFrac) {
					leaveFrac = f;
				}
			}
		}
	}

	//
	// all planes have been checked, and the trace was not
	// completely outside the brush
	//
	if (!startout) {	// original point was inside brush
		tw->trace.startsolid = qtrue;
		if (!getout) {
			tw->trace.allsolid = qtrue;
			tw->trace.fraction = 0;
			tw->trace.contents = brush->contents;
		}
		return;
	}
	
	if (enterFrac < leaveFrac) {
		if (enterFrac > -1 && enterFrac < tw->trace.fraction) {
			if (enterFrac < 0) {
				enterFrac = 0;
			}
			tw->trace.fraction = enterFrac;
			tw->trace.plane = *clipplane;
			tw->trace.surfaceFlags = leadside->surfaceFlags;
			tw->trace.contents = brush->contents;
		}
	}
}