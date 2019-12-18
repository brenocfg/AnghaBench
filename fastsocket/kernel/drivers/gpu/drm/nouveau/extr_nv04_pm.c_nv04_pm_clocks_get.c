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
struct nouveau_pm_level {int core; int memory; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_CORE ; 
 int /*<<< orphan*/  PLL_MEMORY ; 
 int nouveau_hw_get_clock (struct drm_device*,int /*<<< orphan*/ ) ; 

int
nv04_pm_clocks_get(struct drm_device *dev, struct nouveau_pm_level *perflvl)
{
	int ret;

	ret = nouveau_hw_get_clock(dev, PLL_CORE);
	if (ret < 0)
		return ret;
	perflvl->core = ret;

	ret = nouveau_hw_get_clock(dev, PLL_MEMORY);
	if (ret < 0)
		return ret;
	perflvl->memory = ret;

	return 0;
}