#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numpoints; int /*<<< orphan*/  points; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {int numFacets; TYPE_3__* facets; } ;
typedef  TYPE_2__ lsurfaceTest_t ;
struct TYPE_8__ {int numpoints; int /*<<< orphan*/  points; } ;
typedef  TYPE_3__ lFacet_t ;

/* Variables and functions */
 int /*<<< orphan*/  VS_R_LinkSurface (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 TYPE_2__** lsurfaceTest ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int numDrawSurfaces ; 

void VS_LinkSurfaces(void)
{
	int i, j;
	lsurfaceTest_t *test;
	lFacet_t *facet;
	winding_t winding;

	for ( i = 0 ; i < numDrawSurfaces ; i++ )
	{
		test = lsurfaceTest[ i ];
		if (!test)
			continue;
		for (j = 0; j < test->numFacets; j++)
		{
			facet = &test->facets[j];
			memcpy(winding.points, facet->points, facet->numpoints * sizeof(vec3_t));
			winding.numpoints = facet->numpoints;
			VS_R_LinkSurface(0, i, &winding);
		}
	}
}