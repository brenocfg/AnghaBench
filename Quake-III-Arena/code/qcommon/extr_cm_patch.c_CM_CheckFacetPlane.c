#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,float*) ; 
 float SURFACE_CLIP_EPSILON ; 
 int qfalse ; 
 int qtrue ; 

int CM_CheckFacetPlane(float *plane, vec3_t start, vec3_t end, float *enterFrac, float *leaveFrac, int *hit) {
	float d1, d2, f;

	*hit = qfalse;

	d1 = DotProduct( start, plane ) - plane[3];
	d2 = DotProduct( end, plane ) - plane[3];

	// if completely in front of face, no intersection with the entire facet
	if (d1 > 0 && ( d2 >= SURFACE_CLIP_EPSILON || d2 >= d1 )  ) {
		return qfalse;
	}

	// if it doesn't cross the plane, the plane isn't relevent
	if (d1 <= 0 && d2 <= 0 ) {
		return qtrue;
	}

	// crosses face
	if (d1 > d2) {	// enter
		f = (d1-SURFACE_CLIP_EPSILON) / (d1-d2);
		if ( f < 0 ) {
			f = 0;
		}
		//always favor previous plane hits and thus also the surface plane hit
		if (f > *enterFrac) {
			*enterFrac = f;
			*hit = qtrue;
		}
	} else {	// leave
		f = (d1+SURFACE_CLIP_EPSILON) / (d1-d2);
		if ( f > 1 ) {
			f = 1;
		}
		if (f < *leaveFrac) {
			*leaveFrac = f;
		}
	}
	return qtrue;
}