#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * funcs; } ;
struct intel_fbdev {TYPE_2__ helper; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_pipe; struct intel_fbdev* fbdev; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INTELFB_CONN_LIMIT ; 
 int drm_fb_helper_init (struct drm_device*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_single_add_all_connectors (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_fb_helper_funcs ; 
 int /*<<< orphan*/  kfree (struct intel_fbdev*) ; 
 struct intel_fbdev* kzalloc (int,int /*<<< orphan*/ ) ; 

int intel_fbdev_init(struct drm_device *dev)
{
	struct intel_fbdev *ifbdev;
	drm_i915_private_t *dev_priv = dev->dev_private;
	int ret;

	ifbdev = kzalloc(sizeof(struct intel_fbdev), GFP_KERNEL);
	if (!ifbdev)
		return -ENOMEM;

	dev_priv->fbdev = ifbdev;
	ifbdev->helper.funcs = &intel_fb_helper_funcs;

	ret = drm_fb_helper_init(dev, &ifbdev->helper,
				 dev_priv->num_pipe,
				 INTELFB_CONN_LIMIT);
	if (ret) {
		kfree(ifbdev);
		return ret;
	}

	drm_fb_helper_single_add_all_connectors(&ifbdev->helper);

	return 0;
}