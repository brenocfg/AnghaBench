#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct drm_i915_gem_object {TYPE_3__* pages; int /*<<< orphan*/  has_dma_mapping; TYPE_1__ base; } ;
struct drm_device {TYPE_2__* pdev; struct drm_i915_private* dev_private; } ;
struct TYPE_6__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int do_idling (struct drm_i915_private*) ; 
 int /*<<< orphan*/  undo_idling (struct drm_i915_private*,int) ; 

void i915_gem_gtt_finish_object(struct drm_i915_gem_object *obj)
{
	struct drm_device *dev = obj->base.dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	bool interruptible;

	interruptible = do_idling(dev_priv);

	if (!obj->has_dma_mapping)
		dma_unmap_sg(&dev->pdev->dev,
			     obj->pages->sgl, obj->pages->nents,
			     PCI_DMA_BIDIRECTIONAL);

	undo_idling(dev_priv, interruptible);
}