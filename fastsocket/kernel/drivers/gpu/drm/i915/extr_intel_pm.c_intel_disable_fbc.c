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
struct TYPE_2__ {int /*<<< orphan*/  (* disable_fbc ) (struct drm_device*) ;} ;
struct drm_i915_private {int cfb_plane; TYPE_1__ display; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_cancel_fbc_work (struct drm_i915_private*) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 

void intel_disable_fbc(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	intel_cancel_fbc_work(dev_priv);

	if (!dev_priv->display.disable_fbc)
		return;

	dev_priv->display.disable_fbc(dev);
	dev_priv->cfb_plane = -1;
}