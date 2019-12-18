#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ surfaceType; } ;
typedef  TYPE_1__ q3_dsurface_t ;
struct TYPE_7__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ q3_dplane_t ;

/* Variables and functions */
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 scalar_t__ MST_PLANAR ; 
 int /*<<< orphan*/  Q3_SurfacePlane (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* q3_drawSurfaces ; 
 int q3_numDrawSurfaces ; 
 TYPE_2__* q3_surfaceplanes ; 

void Q3_CreatePlanarSurfacePlanes(void)
{
	int i;
	q3_dsurface_t *surface;

	Log_Print("creating planar surface planes...\n");
	q3_surfaceplanes = (q3_dplane_t *) GetClearedMemory(q3_numDrawSurfaces * sizeof(q3_dplane_t));

	for (i = 0; i < q3_numDrawSurfaces; i++)
	{
		surface = &q3_drawSurfaces[i];
		if (surface->surfaceType != MST_PLANAR) continue;
		Q3_SurfacePlane(surface, q3_surfaceplanes[i].normal, &q3_surfaceplanes[i].dist);
		//Log_Print("normal = %f %f %f, dist = %f\n", q3_surfaceplanes[i].normal[0],
		//											q3_surfaceplanes[i].normal[1],
		//											q3_surfaceplanes[i].normal[2], q3_surfaceplanes[i].dist);
	} //end for
}