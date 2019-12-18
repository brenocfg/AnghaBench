#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vsound_t ;
struct TYPE_11__ {TYPE_2__* facets; TYPE_1__* shader; } ;
typedef  TYPE_3__ lsurfaceTest_t ;
struct TYPE_12__ {size_t surfaceNum; size_t facetNum; size_t numtransFacets; size_t* transSurfaces; size_t* transFacets; int* facetTested; int* clusterTested; int /*<<< orphan*/  cluster; int /*<<< orphan*/  farplane; int /*<<< orphan*/  endplane; } ;
typedef  TYPE_4__ lightvolume_t ;
struct TYPE_10__ {int num; } ;
struct TYPE_9__ {int surfaceFlags; int contents; } ;

/* Variables and functions */
 int CONTENTS_TRANSLUCENT ; 
 int /*<<< orphan*/  Error (char*,size_t) ; 
 size_t MAX_TRANSLUCENTFACETS ; 
 int SURF_ALPHASHADOW ; 
 int /*<<< orphan*/  VS_LightSurfaceWithVolume (size_t,size_t,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  VS_R_FloodLight (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** lsurfaceTest ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void VS_R_CastLightAtSurface(vsound_t *light, lightvolume_t *volume)
{
	lsurfaceTest_t *test;
	int i, n;

	// light the surface with this volume
	VS_LightSurfaceWithVolume(volume->surfaceNum, volume->facetNum, light, volume);
	//
	test = lsurfaceTest[ volume->surfaceNum ];
	// if this is not a translucent surface
	if ( !(test->shader->surfaceFlags & SURF_ALPHASHADOW) && !(test->shader->contents & CONTENTS_TRANSLUCENT))
		return;
	//
	if (volume->numtransFacets >= MAX_TRANSLUCENTFACETS)
		Error("a light valume went through more than %d translucent facets", MAX_TRANSLUCENTFACETS);
	//add this translucent surface to the list
	volume->transSurfaces[volume->numtransFacets] = volume->surfaceNum;
	volume->transFacets[volume->numtransFacets] = volume->facetNum;
	volume->numtransFacets++;
	//clear the tested facets except the translucent ones
	memset(volume->facetTested, 0, sizeof(volume->facetTested));
	for (i = 0; i < volume->numtransFacets; i++)
	{
		test = lsurfaceTest[ volume->transSurfaces[i] ];
		n = test->facets[volume->transFacets[i]].num;
		volume->facetTested[n >> 3] |= 1 << (n & 7);
	}
	memset(volume->clusterTested, 0, sizeof(volume->clusterTested));
	volume->endplane = volume->farplane;
	volume->surfaceNum = -1;
	volume->facetNum = 0;
	VS_R_FloodLight(light, volume, volume->cluster, 0);
	if (volume->surfaceNum >= 0)
	{
		VS_R_CastLightAtSurface(light, volume);
	}
}