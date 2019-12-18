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
typedef  float vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */

vec_t CapsuleOriginDistanceFromPlane(vec3_t normal, vec3_t mins, vec3_t maxs)
{
	float offset_up, offset_down, width, radius;

	width = maxs[0] - mins[0];
	// if the box is less high then it is wide
	if (maxs[2] - mins[2] < width) {
		width = maxs[2] - mins[2];
	}
	radius = width * 0.5;
	// offset to upper and lower sphere
	offset_up = maxs[2] - radius;
	offset_down = -mins[2] - radius;

	// if normal points upward
	if ( normal[2] > 0 ) {
		// touches lower sphere first
		return normal[2] * offset_down + radius;
	}
	else {
		// touched upper sphere first
		return -normal[2] * offset_up + radius;
	}
}