#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* pwrctx; TYPE_2__* renderctx; } ;
struct drm_i915_private {TYPE_1__ ips; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (TYPE_2__*) ; 

void ironlake_teardown_rc6(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->ips.renderctx) {
		i915_gem_object_unpin(dev_priv->ips.renderctx);
		drm_gem_object_unreference(&dev_priv->ips.renderctx->base);
		dev_priv->ips.renderctx = NULL;
	}

	if (dev_priv->ips.pwrctx) {
		i915_gem_object_unpin(dev_priv->ips.pwrctx);
		drm_gem_object_unreference(&dev_priv->ips.pwrctx->base);
		dev_priv->ips.pwrctx = NULL;
	}
}