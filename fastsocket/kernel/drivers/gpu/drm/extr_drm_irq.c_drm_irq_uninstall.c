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
struct drm_device {int irq_enabled; int num_crtcs; TYPE_1__* driver; int /*<<< orphan*/  pdev; int /*<<< orphan*/  vbl_lock; int /*<<< orphan*/ * last_vblank; scalar_t__* vblank_enabled; int /*<<< orphan*/ * vbl_queue; int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_uninstall ) (struct drm_device*) ;int /*<<< orphan*/  (* get_vblank_counter ) (struct drm_device*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_IRQ ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_WAKEUP (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_to_irq (struct drm_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct drm_device*) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int drm_irq_uninstall(struct drm_device *dev)
{
	unsigned long irqflags;
	int irq_enabled, i;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		return -EINVAL;

	mutex_lock(&dev->struct_mutex);
	irq_enabled = dev->irq_enabled;
	dev->irq_enabled = 0;
	mutex_unlock(&dev->struct_mutex);

	/*
	 * Wake up any waiters so they don't hang.
	 */
	if (dev->num_crtcs) {
		spin_lock_irqsave(&dev->vbl_lock, irqflags);
		for (i = 0; i < dev->num_crtcs; i++) {
			DRM_WAKEUP(&dev->vbl_queue[i]);
			dev->vblank_enabled[i] = 0;
			dev->last_vblank[i] =
				dev->driver->get_vblank_counter(dev, i);
		}
		spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
	}

	if (!irq_enabled)
		return -EINVAL;

	DRM_DEBUG("irq=%d\n", drm_dev_to_irq(dev));

	if (!drm_core_check_feature(dev, DRIVER_MODESET))
		vga_client_register(dev->pdev, NULL, NULL, NULL);

	if (dev->driver->irq_uninstall)
		dev->driver->irq_uninstall(dev);

	free_irq(drm_dev_to_irq(dev), dev);

	return 0;
}