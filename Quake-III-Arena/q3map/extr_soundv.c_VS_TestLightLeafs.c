#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/ * origin; } ;
typedef  TYPE_1__ vsound_t ;
struct TYPE_6__ {int cluster; } ;
typedef  TYPE_2__ dleaf_t ;

/* Variables and functions */
 scalar_t__ LIGHT_POINTRADIAL ; 
 scalar_t__ LIGHT_POINTSPOT ; 
 int VS_LightLeafnum (int /*<<< orphan*/ *) ; 
 TYPE_2__* dleafs ; 
 int numvsounds ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** vsounds ; 

void VS_TestLightLeafs(void)
{
	int leafnum, i;
	vsound_t *light;
	dleaf_t *leaf;

	for (i = 0; i < numvsounds; i++)
	{
		light = vsounds[i];
		if (light->type != LIGHT_POINTRADIAL &&
			light->type != LIGHT_POINTSPOT)
			continue;
		leafnum = VS_LightLeafnum(light->origin);
		leaf = &dleafs[leafnum];
		if (leaf->cluster == -1)
			if (light->type == LIGHT_POINTRADIAL)
				qprintf("light in solid at %1.1f %1.1f %1.1f\n", light->origin[0], light->origin[1], light->origin[2]);
			else if (light->type == LIGHT_POINTSPOT)
				qprintf("spot light in solid at %1.1f %1.1f %1.1f\n", light->origin[0], light->origin[1], light->origin[2]);
	}
}