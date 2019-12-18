#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsurfaceTest_t ;
struct TYPE_3__ {int lightmapNum; int lightmapHeight; int lightmapWidth; int lightmapY; int lightmapX; } ;
typedef  TYPE_1__ dsurface_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  ColorToBytes (float*,int /*<<< orphan*/ *) ; 
 int LIGHTMAP_HEIGHT ; 
 int LIGHTMAP_WIDTH ; 
 int /*<<< orphan*/  VL_FixLightmapEdges () ; 
 int /*<<< orphan*/  VL_ShiftPatchLightmaps () ; 
 int /*<<< orphan*/  VectorAdd (float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  _printf (char*) ; 
 TYPE_1__* drawSurfaces ; 
 int /*<<< orphan*/  lightAmbientColor ; 
 int /*<<< orphan*/ * lightBytes ; 
 float* lightFloats ; 
 int /*<<< orphan*/ ** lsurfaceTest ; 
 int numDrawSurfaces ; 

void VL_StoreLightmap(void)
{
	int				i, x, y, k;
	dsurface_t		*ds;
	lsurfaceTest_t	*test;
	float			*src;
	byte			*dst;

	_printf("storing lightmaps...\n");
	//fix lightmap edges before storing them
	VL_FixLightmapEdges();
	//
#ifdef LIGHTMAP_PATCHSHIFT
	VL_ShiftPatchLightmaps();
#endif
	//
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
				k = ( ds->lightmapNum * LIGHTMAP_HEIGHT + ds->lightmapY + y)
						* LIGHTMAP_WIDTH + ds->lightmapX + x;
				VectorAdd((lightFloats + k*3), lightAmbientColor, (lightFloats + k*3));
				src = &lightFloats[k*3];
				dst = lightBytes + k*3;
				ColorToBytes(src, dst);
			}
		}
	}
}