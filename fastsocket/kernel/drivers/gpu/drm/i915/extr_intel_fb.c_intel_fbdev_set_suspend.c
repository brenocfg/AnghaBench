#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* obj; } ;
struct TYPE_5__ {struct fb_info* fbdev; } ;
struct intel_fbdev {TYPE_3__ ifb; TYPE_1__ helper; } ;
struct fb_info {int /*<<< orphan*/  screen_size; int /*<<< orphan*/  screen_base; } ;
struct drm_device {TYPE_4__* dev_private; } ;
struct TYPE_8__ {struct intel_fbdev* fbdev; } ;
typedef  TYPE_4__ drm_i915_private_t ;
struct TYPE_6__ {scalar_t__ stolen; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_set_suspend (struct fb_info*,int) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_fbdev_set_suspend(struct drm_device *dev, int state)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct intel_fbdev *ifbdev = dev_priv->fbdev;
	struct fb_info *info;

	if (!ifbdev)
		return;

	info = ifbdev->helper.fbdev;

	/* On resume from hibernation: If the object is shmemfs backed, it has
	 * been restored from swap. If the object is stolen however, it will be
	 * full of whatever garbage was left in there.
	 */
	if (!state && ifbdev->ifb.obj->stolen)
		memset_io(info->screen_base, 0, info->screen_size);

	fb_set_suspend(info, state);
}