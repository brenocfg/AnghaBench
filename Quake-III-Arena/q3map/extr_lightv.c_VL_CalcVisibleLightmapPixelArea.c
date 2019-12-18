#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int numpoints; int /*<<< orphan*/ * points; } ;
typedef  TYPE_2__ winding_t ;
struct TYPE_15__ {int width; TYPE_1__* verts; } ;
typedef  TYPE_3__ mesh_t ;
struct TYPE_16__ {int numFacets; int /*<<< orphan*/ * facets; TYPE_3__* detailMesh; } ;
typedef  TYPE_4__ lsurfaceTest_t ;
struct TYPE_17__ {int lightmapNum; int lightmapHeight; int lightmapWidth; scalar_t__ surfaceType; int lightmapY; int lightmapX; int /*<<< orphan*/ * lightmapVecs; int /*<<< orphan*/  lightmapOrigin; } ;
typedef  TYPE_5__ dsurface_t ;
struct TYPE_13__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  xyz; } ;

/* Variables and functions */
 int LIGHTMAP_HEIGHT ; 
 float LIGHTMAP_PIXELSHIFT ; 
 int LIGHTMAP_WIDTH ; 
 scalar_t__ MST_PATCH ; 
 scalar_t__ VL_ChopWindingWithFacet (TYPE_2__*,int /*<<< orphan*/ *) ; 
 float VL_WindingAreaOutsideSolid (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float WindingArea (TYPE_2__*) ; 
 int /*<<< orphan*/  _printf (char*) ; 
 TYPE_5__* drawSurfaces ; 
 float* lightmappixelarea ; 
 TYPE_4__** lsurfaceTest ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ nostitching ; 
 int numDrawSurfaces ; 

void VL_CalcVisibleLightmapPixelArea(void)
{
	int				i, j, x, y, k;
	dsurface_t		*ds;
	lsurfaceTest_t	*test;
	mesh_t			*mesh;
	winding_t w, tmpw;
	float area;

	_printf("calculating visible lightmap pixel area...\n");
	for ( i = 0 ; i < numDrawSurfaces ; i++ )
	{
		test = lsurfaceTest[ i ];
		if (!test)
			continue;
		ds = &drawSurfaces[ i ];

		if ( ds->lightmapNum < 0 )
			continue;

		for (y = 0; y < ds->lightmapHeight; y++)
		{
			for (x = 0; x < ds->lightmapWidth; x++)
			{
				if (ds->surfaceType == MST_PATCH)
				{
					if (y == ds->lightmapHeight-1)
						continue;
					if (x == ds->lightmapWidth-1)
						continue;
					mesh = lsurfaceTest[i]->detailMesh;
					VectorCopy( mesh->verts[y*mesh->width+x].xyz, w.points[0]);
					VectorCopy( mesh->verts[(y+1)*mesh->width+x].xyz, w.points[1]);
					VectorCopy( mesh->verts[(y+1)*mesh->width+x+1].xyz, w.points[2]);
					VectorCopy( mesh->verts[y*mesh->width+x+1].xyz, w.points[3]);
					w.numpoints = 4;
					if (nostitching)
						area = WindingArea(&w);
					else
						area = VL_WindingAreaOutsideSolid(&w, mesh->verts[y*mesh->width+x].normal);
				}
				else
				{
					VectorMA(ds->lightmapOrigin, (float) x - LIGHTMAP_PIXELSHIFT, ds->lightmapVecs[0], w.points[0]);
					VectorMA(w.points[0], (float) y - LIGHTMAP_PIXELSHIFT, ds->lightmapVecs[1], w.points[0]);
					VectorMA(ds->lightmapOrigin, (float) x - LIGHTMAP_PIXELSHIFT, ds->lightmapVecs[0], w.points[3]);
					VectorMA(w.points[3], (float) y - LIGHTMAP_PIXELSHIFT + 1, ds->lightmapVecs[1], w.points[3]);
					VectorMA(ds->lightmapOrigin, (float) x - LIGHTMAP_PIXELSHIFT + 1, ds->lightmapVecs[0], w.points[2]);
					VectorMA(w.points[2], (float) y - LIGHTMAP_PIXELSHIFT + 1, ds->lightmapVecs[1], w.points[2]);
					VectorMA(ds->lightmapOrigin, (float) x - LIGHTMAP_PIXELSHIFT + 1, ds->lightmapVecs[0], w.points[1]);
					VectorMA(w.points[1], (float) y - LIGHTMAP_PIXELSHIFT, ds->lightmapVecs[1], w.points[1]);
					w.numpoints = 4;
					area = 0;
					for (j = 0; j < test->numFacets; j++)
					{
						memcpy(&tmpw, &w, sizeof(winding_t));
						area += VL_ChopWindingWithFacet(&tmpw, &test->facets[j]);
					}
				}
				k = ( ds->lightmapNum * LIGHTMAP_HEIGHT + ds->lightmapY + y)
						* LIGHTMAP_WIDTH + ds->lightmapX + x;
				lightmappixelarea[k] = area;
			}
		}
	}
}