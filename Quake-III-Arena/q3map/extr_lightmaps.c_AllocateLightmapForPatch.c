#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int width; int height; TYPE_5__* verts; } ;
typedef  TYPE_3__ mesh_t ;
struct TYPE_18__ {int patchWidth; int patchHeight; int lightmapWidth; int lightmapHeight; int lightmapX; int lightmapY; scalar_t__ lightmapNum; TYPE_2__* mapBrush; TYPE_1__* shaderInfo; TYPE_5__* verts; } ;
typedef  TYPE_4__ mapDrawSurface_t ;
struct TYPE_19__ {float* lightmap; } ;
typedef  TYPE_5__ drawVert_t ;
struct TYPE_16__ {int /*<<< orphan*/  brushnum; int /*<<< orphan*/  entitynum; } ;
struct TYPE_15__ {int lightmapSampleSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocLMBlock (int,int,int*,int*) ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeMesh (TYPE_3__*) ; 
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int /*<<< orphan*/  PrepareNewLightmap () ; 
 int /*<<< orphan*/  PutMeshOnCurve (TYPE_3__) ; 
 TYPE_3__* RemoveLinearMeshColumnsRows (TYPE_3__*) ; 
 TYPE_3__* SubdivideMesh (TYPE_3__,int,int) ; 
 TYPE_3__* SubdivideMeshQuads (TYPE_3__*,int,int,int*,int*) ; 
 int c_exactLightmap ; 
 scalar_t__ numLightmaps ; 
 int* originalHeights ; 
 int* originalWidths ; 
 int samplesize ; 

void AllocateLightmapForPatch( mapDrawSurface_t *ds ) {
	int			i, j, k;
	drawVert_t	*verts;
	int			w, h;
	int			x, y;
	float		s, t;
	mesh_t		mesh, *subdividedMesh, *tempMesh, *newmesh;
	int			widthtable[LIGHTMAP_WIDTH], heighttable[LIGHTMAP_HEIGHT], ssize;

	verts = ds->verts;

	mesh.width = ds->patchWidth;
	mesh.height = ds->patchHeight;
	mesh.verts = verts;
	newmesh = SubdivideMesh( mesh, 8, 999 );

	PutMeshOnCurve( *newmesh );
	tempMesh = RemoveLinearMeshColumnsRows( newmesh );
	FreeMesh(newmesh);

	ssize = samplesize;
	if (ds->shaderInfo->lightmapSampleSize)
		ssize = ds->shaderInfo->lightmapSampleSize;

#ifdef LIGHTMAP_PATCHSHIFT
	subdividedMesh = SubdivideMeshQuads( tempMesh, ssize, LIGHTMAP_WIDTH-1, widthtable, heighttable);
#else
	subdividedMesh = SubdivideMeshQuads( tempMesh, ssize, LIGHTMAP_WIDTH, widthtable, heighttable);
#endif

	w = subdividedMesh->width;
	h = subdividedMesh->height;

#ifdef LIGHTMAP_PATCHSHIFT
	w++;
	h++;
#endif

	FreeMesh(subdividedMesh);

	// allocate the lightmap
	c_exactLightmap += w * h;

	if ( !AllocLMBlock( w, h, &x, &y ) ) {
		PrepareNewLightmap();
		if ( !AllocLMBlock( w, h, &x, &y ) ) {
			Error("Entity %i, brush %i: Lightmap allocation failed", 
				ds->mapBrush->entitynum, ds->mapBrush->brushnum );
		}
	}

#ifdef LIGHTMAP_PATCHSHIFT
	w--;
	h--;
#endif

	// set the lightmap texture coordinates in the drawVerts
	ds->lightmapNum = numLightmaps - 1;
	ds->lightmapWidth = w;
	ds->lightmapHeight = h;
	ds->lightmapX = x;
	ds->lightmapY = y;

	for ( i = 0 ; i < ds->patchWidth ; i++ ) {
		for ( k = 0 ; k < w ; k++ ) {
			if ( originalWidths[k] >= i ) {
				break;
			}
		}
		if (k >= w)
			k = w-1;
		s = x + k;
		for ( j = 0 ; j < ds->patchHeight ; j++ ) {
			for ( k = 0 ; k < h ; k++ ) {
				if ( originalHeights[k] >= j ) {
					break;
				}
			}
			if (k >= h)
				k = h-1;
			t = y + k;
			verts[i + j * ds->patchWidth].lightmap[0] = ( s + 0.5 ) / LIGHTMAP_WIDTH;
			verts[i + j * ds->patchWidth].lightmap[1] = ( t + 0.5 ) / LIGHTMAP_HEIGHT;
		}
	}
}