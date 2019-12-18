#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {struct TYPE_5__* hash_chain; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 int CreateNewFloatPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PLANE_HASHES ; 
 scalar_t__ PlaneEqual (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SnapPlane (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 
 TYPE_1__* mapplanes ; 
 int /*<<< orphan*/ * mapplaneusers ; 
 TYPE_1__** planehash ; 

int FindFloatPlane (vec3_t normal, vec_t dist)
{
	int i;
	plane_t *p;
	int hash, h;

	SnapPlane (normal, &dist);
	hash = (int)fabs(dist) / 8;
	hash &= (PLANE_HASHES-1);

	// search the border bins as well
	for (i = -1; i <= 1; i++)
	{
		h = (hash+i)&(PLANE_HASHES-1);
		for (p = planehash[h]; p; p = p->hash_chain)
		{
			if (PlaneEqual(p, normal, dist))
			{
				mapplaneusers[p-mapplanes]++;
				return p - mapplanes;
			} //end if
		} //end for
	} //end for
	i = CreateNewFloatPlane (normal, dist);
	mapplaneusers[i]++;
	return i;
}