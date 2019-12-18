#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nouveau_timer {int (* read ) (struct nouveau_timer*) ;} ;
struct nouveau_pm_profile {TYPE_1__* func; } ;
struct nouveau_pm_level {int id; } ;
struct nouveau_pm {struct nouveau_pm_level* cur; struct nouveau_pm_profile* profile; struct nouveau_pm_profile* profile_dc; struct nouveau_pm_profile* profile_ac; } ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct nouveau_pm_level* (* select ) (struct nouveau_pm_profile*) ;int /*<<< orphan*/  (* init ) (struct nouveau_pm_profile*) ;int /*<<< orphan*/  (* fini ) (struct nouveau_pm_profile*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_pm* nouveau_pm (struct drm_device*) ; 
 int nouveau_pm_perflvl_set (struct drm_device*,struct nouveau_pm_level*) ; 
 struct nouveau_timer* nouveau_timer (int /*<<< orphan*/ ) ; 
 scalar_t__ power_supply_is_system_supplied () ; 
 int /*<<< orphan*/  stub1 (struct nouveau_pm_profile*) ; 
 int /*<<< orphan*/  stub2 (struct nouveau_pm_profile*) ; 
 struct nouveau_pm_level* stub3 (struct nouveau_pm_profile*) ; 
 int stub4 (struct nouveau_timer*) ; 
 int stub5 (struct nouveau_timer*) ; 

void
nouveau_pm_trigger(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_timer *ptimer = nouveau_timer(drm->device);
	struct nouveau_pm *pm = nouveau_pm(dev);
	struct nouveau_pm_profile *profile = NULL;
	struct nouveau_pm_level *perflvl = NULL;
	int ret;

	/* select power profile based on current power source */
	if (power_supply_is_system_supplied())
		profile = pm->profile_ac;
	else
		profile = pm->profile_dc;

	if (profile != pm->profile) {
		pm->profile->func->fini(pm->profile);
		pm->profile = profile;
		pm->profile->func->init(pm->profile);
	}

	/* select performance level based on profile */
	perflvl = profile->func->select(profile);

	/* change perflvl, if necessary */
	if (perflvl != pm->cur) {
		u64 time0 = ptimer->read(ptimer);

		NV_INFO(drm, "setting performance level: %d", perflvl->id);
		ret = nouveau_pm_perflvl_set(dev, perflvl);
		if (ret)
			NV_INFO(drm, "> reclocking failed: %d\n\n", ret);

		NV_INFO(drm, "> reclocking took %lluns\n\n",
			     ptimer->read(ptimer) - time0);
	}
}