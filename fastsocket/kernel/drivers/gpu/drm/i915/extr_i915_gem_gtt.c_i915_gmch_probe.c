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
struct TYPE_3__ {int /*<<< orphan*/  gtt_insert_entries; int /*<<< orphan*/  gtt_clear_range; int /*<<< orphan*/  do_idle_maps; } ;
struct drm_i915_private {TYPE_1__ gtt; TYPE_2__* dev; int /*<<< orphan*/  bridge_dev; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EIO ; 
 int /*<<< orphan*/  i915_ggtt_clear_range ; 
 int /*<<< orphan*/  i915_ggtt_insert_entries ; 
 int intel_gmch_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gtt_get (size_t*,size_t*,int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  needs_idle_maps (TYPE_2__*) ; 

__attribute__((used)) static int i915_gmch_probe(struct drm_device *dev,
			   size_t *gtt_total,
			   size_t *stolen,
			   phys_addr_t *mappable_base,
			   unsigned long *mappable_end)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	ret = intel_gmch_probe(dev_priv->bridge_dev, dev_priv->dev->pdev, NULL);
	if (!ret) {
		DRM_ERROR("failed to set up gmch\n");
		return -EIO;
	}

	intel_gtt_get(gtt_total, stolen, mappable_base, mappable_end);

	dev_priv->gtt.do_idle_maps = needs_idle_maps(dev_priv->dev);
	dev_priv->gtt.gtt_clear_range = i915_ggtt_clear_range;
	dev_priv->gtt.gtt_insert_entries = i915_ggtt_insert_entries;

	return 0;
}