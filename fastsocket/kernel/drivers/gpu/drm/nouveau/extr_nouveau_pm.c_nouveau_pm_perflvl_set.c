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
struct nouveau_pm_level {int dummy; } ;
struct nouveau_pm {int (* clocks_set ) (struct drm_device*,void*) ;struct nouveau_pm_level* cur; void* (* clocks_pre ) (struct drm_device*,struct nouveau_pm_level*) ;} ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int nouveau_pm_perflvl_aux (struct drm_device*,struct nouveau_pm_level*,struct nouveau_pm_level*,struct nouveau_pm_level*) ; 
 void* stub1 (struct drm_device*,struct nouveau_pm_level*) ; 
 int stub2 (struct drm_device*,void*) ; 

__attribute__((used)) static int
nouveau_pm_perflvl_set(struct drm_device *dev, struct nouveau_pm_level *perflvl)
{
	struct nouveau_pm *pm = nouveau_pm(dev);
	void *state;
	int ret;

	if (perflvl == pm->cur)
		return 0;

	ret = nouveau_pm_perflvl_aux(dev, perflvl, pm->cur, perflvl);
	if (ret)
		return ret;

	state = pm->clocks_pre(dev, perflvl);
	if (IS_ERR(state)) {
		ret = PTR_ERR(state);
		goto error;
	}
	ret = pm->clocks_set(dev, state);
	if (ret)
		goto error;

	ret = nouveau_pm_perflvl_aux(dev, perflvl, perflvl, pm->cur);
	if (ret)
		return ret;

	pm->cur = perflvl;
	return 0;

error:
	/* restore the fan speed and voltage before leaving */
	nouveau_pm_perflvl_aux(dev, perflvl, perflvl, pm->cur);
	return ret;
}