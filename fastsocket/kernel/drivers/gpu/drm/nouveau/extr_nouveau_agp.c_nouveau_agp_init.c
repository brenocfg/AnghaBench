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
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  stat; } ;
struct nouveau_drm {TYPE_1__ agp; struct drm_device* dev; int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_agp_mode {int /*<<< orphan*/  mode; } ;
struct drm_agp_info {int /*<<< orphan*/  aperture_size; int /*<<< orphan*/  aperture_base; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLED ; 
 int drm_agp_acquire (struct drm_device*) ; 
 int drm_agp_enable (struct drm_device*,struct drm_agp_mode) ; 
 int drm_agp_info (struct drm_device*,struct drm_agp_info*) ; 
 int /*<<< orphan*/  get_agp_mode (struct nouveau_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_agp_enabled (struct nouveau_drm*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_error (struct nouveau_device*,char*,int) ; 

void
nouveau_agp_init(struct nouveau_drm *drm)
{
#if __OS_HAS_AGP
	struct nouveau_device *device = nv_device(drm->device);
	struct drm_device *dev = drm->dev;
	struct drm_agp_info info;
	struct drm_agp_mode mode;
	int ret;

	if (!nouveau_agp_enabled(drm))
		return;
	drm->agp.stat = DISABLE;

	ret = drm_agp_acquire(dev);
	if (ret) {
		nv_error(device, "unable to acquire AGP: %d\n", ret);
		return;
	}

	ret = drm_agp_info(dev, &info);
	if (ret) {
		nv_error(device, "unable to get AGP info: %d\n", ret);
		return;
	}

	/* see agp.h for the AGPSTAT_* modes available */
	mode.mode = get_agp_mode(drm, info.mode);

	ret = drm_agp_enable(dev, mode);
	if (ret) {
		nv_error(device, "unable to enable AGP: %d\n", ret);
		return;
	}

	drm->agp.stat = ENABLED;
	drm->agp.base = info.aperture_base;
	drm->agp.size = info.aperture_size;
#endif
}