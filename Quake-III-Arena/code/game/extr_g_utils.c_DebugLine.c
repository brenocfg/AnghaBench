#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (TYPE_1__,TYPE_1__,TYPE_1__) ; 
 float DotProduct (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VectorCopy (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VectorMA (TYPE_1__,int,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VectorNormalize (TYPE_1__) ; 
 int /*<<< orphan*/  VectorSet (TYPE_1__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int trap_DebugPolygonCreate (int,int,TYPE_1__*) ; 

int DebugLine(vec3_t start, vec3_t end, int color) {
	vec3_t points[4], dir, cross, up = {0, 0, 1};
	float dot;

	VectorCopy(start, points[0]);
	VectorCopy(start, points[1]);
	//points[1][2] -= 2;
	VectorCopy(end, points[2]);
	//points[2][2] -= 2;
	VectorCopy(end, points[3]);


	VectorSubtract(end, start, dir);
	VectorNormalize(dir);
	dot = DotProduct(dir, up);
	if (dot > 0.99 || dot < -0.99) VectorSet(cross, 1, 0, 0);
	else CrossProduct(dir, up, cross);

	VectorNormalize(cross);

	VectorMA(points[0], 2, cross, points[0]);
	VectorMA(points[1], -2, cross, points[1]);
	VectorMA(points[2], -2, cross, points[2]);
	VectorMA(points[3], 2, cross, points[3]);

	return trap_DebugPolygonCreate(color, 4, points);
}