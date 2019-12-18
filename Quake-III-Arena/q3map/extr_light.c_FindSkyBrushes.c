#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int** bounds; TYPE_4__* b; } ;
typedef  TYPE_1__ skyBrush_t ;
struct TYPE_13__ {int surfaceFlags; int /*<<< orphan*/  sunDirection; int /*<<< orphan*/  sunLight; } ;
typedef  TYPE_2__ shaderInfo_t ;
struct TYPE_14__ {size_t shaderNum; size_t planeNum; } ;
typedef  TYPE_3__ dbrushside_t ;
struct TYPE_15__ {int numSides; int firstSide; } ;
typedef  TYPE_4__ dbrush_t ;
struct TYPE_18__ {int dist; } ;
struct TYPE_17__ {size_t shaderNum; } ;
struct TYPE_16__ {int surfaceFlags; int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 int SURF_SKY ; 
 TYPE_2__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* dbrushes ; 
 TYPE_3__* dbrushsides ; 
 TYPE_8__* dplanes ; 
 TYPE_7__* drawSurfaces ; 
 TYPE_6__* dshaders ; 
 int numDrawSurfaces ; 
 size_t numSkyBrushes ; 
 int numbrushes ; 
 TYPE_1__* skyBrushes ; 
 int /*<<< orphan*/  sunDirection ; 
 int /*<<< orphan*/  sunLight ; 

void FindSkyBrushes( void ) {
	int				i, j;
	dbrush_t		*b;
	skyBrush_t		*sb;
	shaderInfo_t	*si;
	dbrushside_t	*s;

	// find the brushes
	for ( i = 0 ; i < numbrushes ; i++ ) {
		b = &dbrushes[i];
		for ( j = 0 ; j < b->numSides ; j++ ) {
			s = &dbrushsides[ b->firstSide + j ];
			if ( dshaders[ s->shaderNum ].surfaceFlags & SURF_SKY ) {
				sb = &skyBrushes[ numSkyBrushes ];
				sb->b = b;
				sb->bounds[0][0] = -dplanes[ dbrushsides[ b->firstSide + 0 ].planeNum ].dist - 1;
				sb->bounds[1][0] = dplanes[ dbrushsides[ b->firstSide + 1 ].planeNum ].dist + 1;
				sb->bounds[0][1] = -dplanes[ dbrushsides[ b->firstSide + 2 ].planeNum ].dist - 1;
				sb->bounds[1][1] = dplanes[ dbrushsides[ b->firstSide + 3 ].planeNum ].dist + 1;
				sb->bounds[0][2] = -dplanes[ dbrushsides[ b->firstSide + 4 ].planeNum ].dist - 1;
				sb->bounds[1][2] = dplanes[ dbrushsides[ b->firstSide + 5 ].planeNum ].dist + 1;
				numSkyBrushes++;
				break;
			}
		}
	}

	// default
	VectorNormalize( sunDirection, sunDirection );

	// find the sky shader
	for ( i = 0 ; i < numDrawSurfaces ; i++ ) {
		si = ShaderInfoForShader( dshaders[ drawSurfaces[i].shaderNum ].shader );
		if ( si->surfaceFlags & SURF_SKY ) {
			VectorCopy( si->sunLight, sunLight );
			VectorCopy( si->sunDirection, sunDirection );
			break;
		}
	}
}