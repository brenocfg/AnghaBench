#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {TYPE_1__* vertexes; } ;
struct TYPE_3__ {float* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DotProduct (float*,int /*<<< orphan*/ ) ; 
 int TH_FindFloatPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,int /*<<< orphan*/ ) ; 
 TYPE_2__ thworld ; 

int TH_PlaneFromPoints(int v1, int v2, int v3)
{
	vec3_t t1, t2, normal;
	vec_t dist;
	float *p0, *p1, *p2;

	p0 = thworld.vertexes[v1].v;
	p1 = thworld.vertexes[v2].v;
	p2 = thworld.vertexes[v3].v;

	VectorSubtract(p0, p1, t1);
	VectorSubtract(p2, p1, t2);
	CrossProduct(t1, t2, normal);
	VectorNormalize(normal);

	dist = DotProduct(p0, normal);

	return TH_FindFloatPlane(normal, dist);
}