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
typedef  int /*<<< orphan*/  terrainVert_t ;
typedef  int /*<<< orphan*/  terrainMesh_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Terrain_GetVert (int /*<<< orphan*/ *,int,int) ; 

void Terrain_GetTriangles( terrainMesh_t *pm, int x, int y, terrainVert_t **verts ) {
	if ( ( x + y ) & 1 ) {
		// first tri
		verts[ 0 ] = Terrain_GetVert( pm, x, y );
		verts[ 1 ] = Terrain_GetVert( pm, x, y + 1 );
		verts[ 2 ] = Terrain_GetVert( pm, x + 1, y + 1 );

		// second tri
		verts[ 3 ] = verts[ 2 ];
		verts[ 4 ] = Terrain_GetVert( pm, x + 1, y );
		verts[ 5 ] = verts[ 0 ];
	} else {
		// first tri
		verts[ 0 ] = Terrain_GetVert( pm, x, y );
		verts[ 1 ] = Terrain_GetVert( pm, x, y + 1 );
		verts[ 2 ] = Terrain_GetVert( pm, x + 1, y );

		// second tri
		verts[ 3 ] = verts[ 2 ];
		verts[ 4 ] = verts[ 1 ];
		verts[ 5 ] = Terrain_GetVert( pm, x + 1, y + 1 );
	}
}