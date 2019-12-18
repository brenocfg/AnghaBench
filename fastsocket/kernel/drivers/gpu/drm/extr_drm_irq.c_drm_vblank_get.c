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
struct drm_device {int* vblank_enabled; int /*<<< orphan*/  vbl_lock; int /*<<< orphan*/ * vblank_refcount; int /*<<< orphan*/  vblank_time_lock; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* enable_vblank ) (struct drm_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int EINVAL ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_update_vblank_count (struct drm_device*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct drm_device*,int) ; 

int drm_vblank_get(struct drm_device *dev, int crtc)
{
	unsigned long irqflags, irqflags2;
	int ret = 0;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	/* Going from 0->1 means we have to enable interrupts again */
	if (atomic_add_return(1, &dev->vblank_refcount[crtc]) == 1) {
		spin_lock_irqsave(&dev->vblank_time_lock, irqflags2);
		if (!dev->vblank_enabled[crtc]) {
			/* Enable vblank irqs under vblank_time_lock protection.
			 * All vblank count & timestamp updates are held off
			 * until we are done reinitializing master counter and
			 * timestamps. Filtercode in drm_handle_vblank() will
			 * prevent double-accounting of same vblank interval.
			 */
			ret = dev->driver->enable_vblank(dev, crtc);
			DRM_DEBUG("enabling vblank on crtc %d, ret: %d\n",
				  crtc, ret);
			if (ret)
				atomic_dec(&dev->vblank_refcount[crtc]);
			else {
				dev->vblank_enabled[crtc] = 1;
				drm_update_vblank_count(dev, crtc);
			}
		}
		spin_unlock_irqrestore(&dev->vblank_time_lock, irqflags2);
	} else {
		if (!dev->vblank_enabled[crtc]) {
			atomic_dec(&dev->vblank_refcount[crtc]);
			ret = -EINVAL;
		}
	}
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);

	return ret;
}