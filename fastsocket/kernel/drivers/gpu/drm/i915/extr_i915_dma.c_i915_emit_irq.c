#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_i915_master_private {TYPE_3__* sarea_priv; } ;
struct drm_device {TYPE_2__* primary; TYPE_5__* dev_private; } ;
struct TYPE_9__ {int counter; } ;
struct TYPE_10__ {TYPE_4__ dri1; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_8__ {int last_enqueue; } ;
struct TYPE_7__ {TYPE_1__* master; } ;
struct TYPE_6__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_LP_RING () ; 
 scalar_t__ BEGIN_LP_RING (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int I915_BREADCRUMB_INDEX ; 
 int MI_STORE_DWORD_INDEX ; 
 int MI_STORE_DWORD_INDEX_SHIFT ; 
 int MI_USER_INTERRUPT ; 
 int /*<<< orphan*/  OUT_RING (int) ; 
 int /*<<< orphan*/  i915_kernel_lost_context (struct drm_device*) ; 

__attribute__((used)) static int i915_emit_irq(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;

	i915_kernel_lost_context(dev);

	DRM_DEBUG_DRIVER("\n");

	dev_priv->dri1.counter++;
	if (dev_priv->dri1.counter > 0x7FFFFFFFUL)
		dev_priv->dri1.counter = 1;
	if (master_priv->sarea_priv)
		master_priv->sarea_priv->last_enqueue = dev_priv->dri1.counter;

	if (BEGIN_LP_RING(4) == 0) {
		OUT_RING(MI_STORE_DWORD_INDEX);
		OUT_RING(I915_BREADCRUMB_INDEX << MI_STORE_DWORD_INDEX_SHIFT);
		OUT_RING(dev_priv->dri1.counter);
		OUT_RING(MI_USER_INTERRUPT);
		ADVANCE_LP_RING();
	}

	return dev_priv->dri1.counter;
}