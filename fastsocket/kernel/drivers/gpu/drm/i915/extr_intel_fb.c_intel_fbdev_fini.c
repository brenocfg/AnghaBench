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
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fbdev; } ;
typedef  TYPE_1__ drm_i915_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  intel_fbdev_destroy (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void intel_fbdev_fini(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	if (!dev_priv->fbdev)
		return;

	intel_fbdev_destroy(dev, dev_priv->fbdev);
	kfree(dev_priv->fbdev);
	dev_priv->fbdev = NULL;
}