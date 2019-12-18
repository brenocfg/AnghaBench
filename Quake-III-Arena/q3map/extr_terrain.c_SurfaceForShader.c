#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int x; int y; int /*<<< orphan*/ * shader; } ;
typedef  TYPE_1__ terrainSurf_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;

/* Variables and functions */
 scalar_t__ GROW_SURFACES ; 
 TYPE_1__* lastSurface ; 
 int maxsurfaces ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numsurfaces ; 
 TYPE_1__* realloc (TYPE_1__*,int) ; 
 TYPE_1__* surfaces ; 

terrainSurf_t *SurfaceForShader( shaderInfo_t *shader, int x, int y ) {
	int i;

	if ( lastSurface && ( lastSurface->shader == shader ) && ( lastSurface->x == x ) && ( lastSurface->y == y ) ) {
		return lastSurface;
	}

	lastSurface = surfaces;
	for( i = 0; i < numsurfaces; i++, lastSurface++ ) {
		if ( ( lastSurface->shader == shader ) && ( lastSurface->x == x ) && ( lastSurface->y == y ) ) {
			return lastSurface;
		}
	}

	if ( numsurfaces >= maxsurfaces ) {
		maxsurfaces += GROW_SURFACES;
		surfaces = realloc( surfaces, maxsurfaces * sizeof( *surfaces ) );
		memset( surfaces + numsurfaces + 1, 0, ( maxsurfaces - numsurfaces - 1 ) * sizeof( *surfaces ) );
	}

	lastSurface= &surfaces[ numsurfaces++ ];
	lastSurface->shader = shader;
	lastSurface->x = x;
	lastSurface->y = y;

	return lastSurface;
}