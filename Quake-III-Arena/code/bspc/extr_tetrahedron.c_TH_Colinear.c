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
 int /*<<< orphan*/  CrossProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float VectorLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (float*,float*,int /*<<< orphan*/ ) ; 

int TH_Colinear(float *v0, float *v1, float *v2)
{
	vec3_t t1, t2, vcross;
	float d;
	
	VectorSubtract(v1, v0, t1);
	VectorSubtract(v2, v0, t2);
	CrossProduct (t1, t2, vcross);
	d = VectorLength( vcross );

	// if cross product is zero point is colinear
	if (d < 10)
	{
		return true;
	} //end if
	return false;
}