#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xyz; } ;
typedef  TYPE_1__ terrainVert_t ;
struct TYPE_5__ {int height; int width; TYPE_1__* map; } ;
typedef  TYPE_2__ terrainMesh_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeBrushFromTriangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ShaderInfoForShader (char*) ; 

void MakeTerrainIntoBrushes( terrainMesh_t *tm ) {
	int				index[ 6 ];
	int				y;
	int				x;
	terrainVert_t	*verts;
	shaderInfo_t	*terrainShader;

	terrainShader = ShaderInfoForShader( "textures/common/terrain" );

	verts = tm->map;
	for( y = 0; y < tm->height - 1; y++ ) {
		for( x = 0; x < tm->width - 1; x++ ) {
			if ( ( x + y ) & 1 ) {
				// first tri
				index[ 0 ] = x + y * tm->width;
				index[ 1 ] = x + ( y + 1 ) * tm->width;
				index[ 2 ] = ( x + 1 ) + ( y + 1 ) * tm->width;
				index[ 3 ] = ( x + 1 ) + ( y + 1 ) * tm->width;
				index[ 4 ] = ( x + 1 ) + y * tm->width;
				index[ 5 ] = x + y * tm->width;
			} else {
				// first tri
				index[ 0 ] = x + y * tm->width;
				index[ 1 ] = x + ( y + 1 ) * tm->width;
				index[ 2 ] = ( x + 1 ) + y * tm->width;
				index[ 3 ] = ( x + 1 ) + y * tm->width;
				index[ 4 ] = x + ( y + 1 ) * tm->width;
				index[ 5 ] = ( x + 1 ) + ( y + 1 ) * tm->width;
			}

			MakeBrushFromTriangle( verts[ index[ 0 ] ].xyz, verts[ index[ 1 ] ].xyz, verts[ index[ 2 ] ].xyz, terrainShader );
			MakeBrushFromTriangle( verts[ index[ 3 ] ].xyz, verts[ index[ 4 ] ].xyz, verts[ index[ 5 ] ].xyz, terrainShader );
		}
	}
}