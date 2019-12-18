#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {float dist; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreateRotationMatrix (int /*<<< orphan*/ ,float**) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FindFloatPlane (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  RotatePoint (int /*<<< orphan*/ ,float**) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mapplanes ; 

int AAS_TransformPlane(int planenum, vec3_t origin, vec3_t angles)
{
	float newdist, matrix[3][3];
	vec3_t normal;

	//rotate the node plane
	VectorCopy(mapplanes[planenum].normal, normal);
	CreateRotationMatrix(angles, matrix);
	RotatePoint(normal, matrix);
	newdist = mapplanes[planenum].dist + DotProduct(normal, origin);
	return FindFloatPlane(normal, newdist);
}