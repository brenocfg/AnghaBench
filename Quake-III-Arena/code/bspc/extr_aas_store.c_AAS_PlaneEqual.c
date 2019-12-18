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
typedef  float* vec3_t ;
struct TYPE_4__ {TYPE_1__* planes; } ;
struct TYPE_3__ {float dist; float* normal; } ;

/* Variables and functions */
 float DIST_EPSILON ; 
 float NORMAL_EPSILON ; 
 TYPE_2__ aasworld ; 

int AAS_PlaneEqual(vec3_t normal, float dist, int planenum)
{
	float diff;

	diff = dist - aasworld.planes[planenum].dist;
	if (diff > -DIST_EPSILON && diff < DIST_EPSILON)
	{
		diff = normal[0] - aasworld.planes[planenum].normal[0];
		if (diff > -NORMAL_EPSILON && diff < NORMAL_EPSILON)
		{
			diff = normal[1] - aasworld.planes[planenum].normal[1];
			if (diff > -NORMAL_EPSILON && diff < NORMAL_EPSILON)
			{
				diff = normal[2] - aasworld.planes[planenum].normal[2];
				if (diff > -NORMAL_EPSILON && diff < NORMAL_EPSILON)
				{
					return true;
				} //end if
			} //end if
		} //end if
	} //end if
	return false;
}