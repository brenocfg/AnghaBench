#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  traceWork_t ;
struct TYPE_7__ {int /*<<< orphan*/  vertexScale; int /*<<< orphan*/  forceSunLight; int /*<<< orphan*/  vertexShadows; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_8__ {scalar_t__ surfaceType; int lightmapNum; size_t shaderNum; } ;
typedef  TYPE_2__ dsurface_t ;
struct TYPE_9__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 scalar_t__ MST_TRIANGLE_SOUP ; 
 TYPE_1__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VertexLighting (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* drawSurfaces ; 
 TYPE_3__* dshaders ; 
 scalar_t__ novertexlighting ; 

void VertexLightingThread(int num) {
	dsurface_t	*ds;
	traceWork_t	tw;
	shaderInfo_t *si;

	ds = &drawSurfaces[num];

	// vertex-lit triangle model
	if ( ds->surfaceType == MST_TRIANGLE_SOUP ) {
		return;
	}

	if (novertexlighting)
		return;

	if ( ds->lightmapNum == -1 ) {
		return;	// doesn't need lighting at all
	}

	si = ShaderInfoForShader( dshaders[ ds->shaderNum].shader );

	// calculate the vertex lighting for gouraud shade mode
	VertexLighting( ds, si->vertexShadows, si->forceSunLight, si->vertexScale, &tw );
}