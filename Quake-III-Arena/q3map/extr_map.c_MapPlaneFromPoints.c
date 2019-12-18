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
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FindFloatPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int MapPlaneFromPoints (vec3_t p0, vec3_t p1, vec3_t p2) {
	vec3_t	t1, t2, normal;
	vec_t	dist;

	VectorSubtract (p0, p1, t1);
	VectorSubtract (p2, p1, t2);
	CrossProduct (t1, t2, normal);
	VectorNormalize (normal, normal);

	dist = DotProduct (p0, normal);

	return FindFloatPlane (normal, dist);
}