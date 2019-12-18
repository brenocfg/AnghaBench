#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int numpoints; int /*<<< orphan*/  points; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_11__ {size_t shaderNum; } ;
typedef  TYPE_2__ dbrush_t ;
struct TYPE_12__ {int contentFlags; } ;

/* Variables and functions */
 int CONTENTS_AREAPORTAL ; 
 int CONTENTS_BODY ; 
 int CONTENTS_CLUSTERPORTAL ; 
 int CONTENTS_CORPSE ; 
 int CONTENTS_DONOTENTER ; 
 int CONTENTS_FOG ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_MONSTERCLIP ; 
 int CONTENTS_NODROP ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_TRANSLUCENT ; 
 int CONTENTS_TRIGGER ; 
 int CONTENTS_WATER ; 
 int VL_ChopWindingWithBrush (TYPE_1__*,TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ WindingArea (TYPE_1__*) ; 
 TYPE_2__* dbrushes ; 
 TYPE_3__* dshaders ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

float VL_WindingAreaOutsideBrushes(winding_t *w, int *brushnums, int numbrushes)
{
	int i, j, numwindings[2], n;
	winding_t windingsbuf[2][64];
	dbrush_t *brush;
	float area;

	memcpy(windingsbuf[0][0].points, w->points, w->numpoints * sizeof(vec3_t));
	windingsbuf[0][0].numpoints = w->numpoints;
	numwindings[0] = 1;
	for (i = 0; i < numbrushes; i++)
	{
		brush = &dbrushes[brushnums[i]];
		if (!(dshaders[brush->shaderNum].contentFlags & (
					CONTENTS_LAVA
					| CONTENTS_SLIME
					| CONTENTS_WATER
					| CONTENTS_FOG
					| CONTENTS_AREAPORTAL
					| CONTENTS_PLAYERCLIP
					| CONTENTS_MONSTERCLIP
					| CONTENTS_CLUSTERPORTAL
					| CONTENTS_DONOTENTER
					| CONTENTS_BODY
					| CONTENTS_CORPSE
					| CONTENTS_TRANSLUCENT
					| CONTENTS_TRIGGER
					| CONTENTS_NODROP) ) &&
			(dshaders[brush->shaderNum].contentFlags & CONTENTS_SOLID) )
		{
			numwindings[!(i & 1)] = 0;
			for (j = 0; j < numwindings[i&1]; j++)
			{
				n = VL_ChopWindingWithBrush(&windingsbuf[i&1][j], brush,
											&windingsbuf[!(i&1)][numwindings[!(i&1)]],
											64 - numwindings[!(i&1)]);
				numwindings[!(i&1)] += n;
			}
			if (!numwindings[!(i&1)])
				return 0;
		}
		else
		{
			for (j = 0; j < numwindings[i&1]; j++)
			{
				windingsbuf[!(i&1)][j] = windingsbuf[i&1][j];
			}
			numwindings[!(i&1)] = numwindings[i&1];
		}
	}
	area = 0;
	for (j = 0; j < numwindings[i&1]; j++)
	{
		area += WindingArea(&windingsbuf[i&1][j]);
	}
	return area;
}