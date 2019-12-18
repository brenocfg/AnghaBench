#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_4__ {int planenum; int /*<<< orphan*/ * shaderInfo; } ;
typedef  TYPE_1__ side_t ;
typedef  int /*<<< orphan*/  shaderInfo_t ;
struct TYPE_5__ {size_t numsides; TYPE_1__* sides; } ;

/* Variables and functions */
 int MapPlaneFromPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* buildBrush ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void AddBrushSide( vec3_t v1, vec3_t v2, vec3_t v3, shaderInfo_t *terrainShader ) {
	side_t	*side;
	int		planenum;

	side = &buildBrush->sides[ buildBrush->numsides ];
	memset( side, 0, sizeof( *side ) );
	buildBrush->numsides++;

	side->shaderInfo = terrainShader;

	// find the plane number
	planenum = MapPlaneFromPoints( v1, v2, v3 );
	side->planenum = planenum;
}