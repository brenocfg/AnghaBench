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
struct TYPE_2__ {int /*<<< orphan*/ * pwrctx; int /*<<< orphan*/ * renderctx; } ;
struct drm_i915_private {TYPE_1__ ips; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* intel_alloc_context_page (struct drm_device*) ; 
 int /*<<< orphan*/  ironlake_teardown_rc6 (struct drm_device*) ; 

__attribute__((used)) static int ironlake_setup_rc6(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (dev_priv->ips.renderctx == NULL)
		dev_priv->ips.renderctx = intel_alloc_context_page(dev);
	if (!dev_priv->ips.renderctx)
		return -ENOMEM;

	if (dev_priv->ips.pwrctx == NULL)
		dev_priv->ips.pwrctx = intel_alloc_context_page(dev);
	if (!dev_priv->ips.pwrctx) {
		ironlake_teardown_rc6(dev);
		return -ENOMEM;
	}

	return 0;
}