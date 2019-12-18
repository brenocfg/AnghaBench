#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  forceTraceLight; scalar_t__ forceVLight; } ;
typedef  TYPE_1__ shaderInfo_t ;
struct TYPE_7__ {scalar_t__ surfaceType; scalar_t__ lightmapNum; size_t shaderNum; } ;
typedef  TYPE_2__ dsurface_t ;
struct TYPE_8__ {int /*<<< orphan*/  shader; } ;

/* Variables and functions */
 scalar_t__ MST_TRIANGLE_SOUP ; 
 TYPE_1__* ShaderInfoForShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TraceLtm (int) ; 
 scalar_t__ defaulttracelight ; 
 TYPE_2__* drawSurfaces ; 
 TYPE_3__* dshaders ; 
 int /*<<< orphan*/ * entitySurface ; 

void VL_DoForcedTraceLight(int num)
{
	dsurface_t		*ds;
	shaderInfo_t	*si;

	ds = &drawSurfaces[num];

	if ( ds->surfaceType == MST_TRIANGLE_SOUP )
		return;

	if ( ds->lightmapNum < 0 )
		return;

	// always light entity surfaces with the old light algorithm
	if ( !entitySurface[num] )
	{
		si = ShaderInfoForShader( dshaders[ ds->shaderNum].shader );

		if (defaulttracelight)
		{
			if (si->forceVLight)
				return;
		}
		else
		{
			if (!si->forceTraceLight)
				return;
		}
	}

	TraceLtm(num);
}