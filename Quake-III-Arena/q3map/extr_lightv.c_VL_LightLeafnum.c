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
 int VL_PointInLeafnum (int /*<<< orphan*/ ) ; 

int VL_LightLeafnum(vec3_t point)
{
	/*
	int leafnum;
	dleaf_t *leaf;
	float x, y, z;
	vec3_t test;

	leafnum = VL_PointInLeafnum(point);
	leaf = &dleafs[leafnum];
	if (leaf->cluster != -1)
		return leafnum;
	for (z = 1; z >= -1; z -= 1)
	{
		for (x = 1; x >= -1; x -= 1)
		{
			for (y = 1; y >= -1; y -= 1)
			{
				VectorCopy(point, test);
				test[0] += x;
				test[1] += y;
				test[2] += z;
				leafnum = VL_PointInLeafnum(test);
				leaf = &dleafs[leafnum];
				if (leaf->cluster != -1)
				{
					VectorCopy(test, point);
					return leafnum;
				}
			}
		}
	}
	return leafnum;
	*/
	return VL_PointInLeafnum(point);
}