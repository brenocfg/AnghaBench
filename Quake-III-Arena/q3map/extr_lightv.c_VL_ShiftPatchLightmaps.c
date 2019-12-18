#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsurfaceTest_t ;
struct TYPE_5__ {int lightmapNum; scalar_t__ surfaceType; int lightmapWidth; int lightmapHeight; int lightmapY; int lightmapX; size_t firstVert; int patchHeight; int patchWidth; } ;
typedef  TYPE_1__ dsurface_t ;
struct TYPE_6__ {double* lightmap; } ;
typedef  TYPE_2__ drawVert_t ;

/* Variables and functions */
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 scalar_t__ MST_PATCH ; 
 TYPE_1__* drawSurfaces ; 
 TYPE_2__* drawVerts ; 
 float* lightFloats ; 
 int /*<<< orphan*/ ** lsurfaceTest ; 
 int numDrawSurfaces ; 

void VL_ShiftPatchLightmaps(void)
{
	int				i, j, x, y, k;
	drawVert_t		*verts;
	dsurface_t		*ds;
	lsurfaceTest_t	*test;
	float			*ptr;

	for ( i = 0 ; i < numDrawSurfaces ; i++ )
	{
		test = lsurfaceTest[ i ];
		if (!test)
			continue;
		ds = &drawSurfaces[ i ];

		if ( ds->lightmapNum < 0 )
			continue;
		if (ds->surfaceType != MST_PATCH)
			continue;
		for (x = ds->lightmapWidth; x > 0; x--)
		{
			for (y = 0; y <= ds->lightmapHeight; y++)
			{
				k = ( ds->lightmapNum * LIGHTMAP_HEIGHT + ds->lightmapY + y)
						* LIGHTMAP_WIDTH + ds->lightmapX + x;
				ptr = lightFloats + k*3;
				ptr[0] = (lightFloats + (k-1)*3)[0];
				ptr[1] = (lightFloats + (k-1)*3)[1];
				ptr[2] = (lightFloats + (k-1)*3)[2];
			}
		}
		for (y = ds->lightmapHeight; y > 0; y--)
		{
			for (x = 0; x <= ds->lightmapWidth; x++)
			{
				k = ( ds->lightmapNum * LIGHTMAP_HEIGHT + ds->lightmapY + y)
						* LIGHTMAP_WIDTH + ds->lightmapX + x;
				ptr = lightFloats + k*3;
				ptr[0] = (lightFloats + (k-LIGHTMAP_WIDTH)*3)[0];
				ptr[1] = (lightFloats + (k-LIGHTMAP_WIDTH)*3)[1];
				ptr[2] = (lightFloats + (k-LIGHTMAP_WIDTH)*3)[2];
			}
		}
		verts = &drawVerts[ ds->firstVert ];
		for ( j = 0 ; j < ds->patchHeight * ds->patchWidth; j++ )
		{
			verts[j].lightmap[0] += 0.5 / LIGHTMAP_WIDTH;
			verts[j].lightmap[1] += 0.5 / LIGHTMAP_HEIGHT;
		}
		ds->lightmapHeight++;
		ds->lightmapWidth++;
	}
}