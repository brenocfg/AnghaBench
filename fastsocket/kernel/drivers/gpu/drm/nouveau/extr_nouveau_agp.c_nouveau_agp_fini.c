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
struct nouveau_drm {struct drm_device* dev; } ;
struct drm_device {TYPE_1__* agp; } ;
struct TYPE_2__ {scalar_t__ acquired; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_agp_release (struct drm_device*) ; 

void
nouveau_agp_fini(struct nouveau_drm *drm)
{
#if __OS_HAS_AGP
	struct drm_device *dev = drm->dev;
	if (dev->agp && dev->agp->acquired)
		drm_agp_release(dev);
#endif
}