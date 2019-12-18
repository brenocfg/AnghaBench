#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq_lock; } ;
typedef  TYPE_1__ drm_i915_private_t ;
struct TYPE_6__ {int gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_GSE ; 
 scalar_t__ HAS_PCH_SPLIT (struct drm_device*) ; 
 TYPE_4__* INTEL_INFO (struct drm_device*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_device*) ; 
 int /*<<< orphan*/  PIPE_LEGACY_BLC_EVENT_ENABLE ; 
 int /*<<< orphan*/  i915_enable_pipestat (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ironlake_enable_display_irq (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intel_enable_asle(struct drm_device *dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	unsigned long irqflags;

	/* FIXME: opregion/asle for VLV */
	if (IS_VALLEYVIEW(dev))
		return;

	spin_lock_irqsave(&dev_priv->irq_lock, irqflags);

	if (HAS_PCH_SPLIT(dev))
		ironlake_enable_display_irq(dev_priv, DE_GSE);
	else {
		i915_enable_pipestat(dev_priv, 1,
				     PIPE_LEGACY_BLC_EVENT_ENABLE);
		if (INTEL_INFO(dev)->gen >= 4)
			i915_enable_pipestat(dev_priv, 0,
					     PIPE_LEGACY_BLC_EVENT_ENABLE);
	}

	spin_unlock_irqrestore(&dev_priv->irq_lock, irqflags);
}