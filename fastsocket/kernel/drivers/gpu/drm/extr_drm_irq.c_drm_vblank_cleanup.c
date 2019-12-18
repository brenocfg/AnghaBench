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
struct drm_device {scalar_t__ num_crtcs; int /*<<< orphan*/  _vblank_time; int /*<<< orphan*/  vblank_inmodeset; int /*<<< orphan*/  last_vblank_wait; int /*<<< orphan*/  last_vblank; int /*<<< orphan*/  vblank_enabled; int /*<<< orphan*/  vblank_refcount; int /*<<< orphan*/  _vblank_count; int /*<<< orphan*/  vbl_queue; int /*<<< orphan*/  vblank_disable_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vblank_disable_fn (unsigned long) ; 

void drm_vblank_cleanup(struct drm_device *dev)
{
	/* Bail if the driver didn't call drm_vblank_init() */
	if (dev->num_crtcs == 0)
		return;

	del_timer_sync(&dev->vblank_disable_timer);

	vblank_disable_fn((unsigned long)dev);

	kfree(dev->vbl_queue);
	kfree(dev->_vblank_count);
	kfree(dev->vblank_refcount);
	kfree(dev->vblank_enabled);
	kfree(dev->last_vblank);
	kfree(dev->last_vblank_wait);
	kfree(dev->vblank_inmodeset);
	kfree(dev->_vblank_time);

	dev->num_crtcs = 0;
}