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
struct intel_ring_buffer {int head; int tail; scalar_t__ space; scalar_t__ size; } ;
struct drm_i915_master_private {TYPE_3__* sarea_priv; } ;
struct drm_device {TYPE_2__* primary; int /*<<< orphan*/ * dev_private; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  perf_boxes; } ;
struct TYPE_5__ {TYPE_1__* master; } ;
struct TYPE_4__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int HEAD_ADDR ; 
 int /*<<< orphan*/  I915_BOX_RING_EMPTY ; 
 int I915_READ_HEAD (struct intel_ring_buffer*) ; 
 int I915_READ_TAIL (struct intel_ring_buffer*) ; 
 scalar_t__ I915_RING_FREE_SPACE ; 
 struct intel_ring_buffer* LP_RING (int /*<<< orphan*/ *) ; 
 int TAIL_ADDR ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 

void i915_kernel_lost_context(struct drm_device * dev)
{
	drm_i915_private_t *dev_priv = dev->dev_private;
	struct drm_i915_master_private *master_priv;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	/*
	 * We should never lose context on the ring with modesetting
	 * as we don't expose it to userspace
	 */
	if (drm_core_check_feature(dev, DRIVER_MODESET))
		return;

	ring->head = I915_READ_HEAD(ring) & HEAD_ADDR;
	ring->tail = I915_READ_TAIL(ring) & TAIL_ADDR;
	ring->space = ring->head - (ring->tail + I915_RING_FREE_SPACE);
	if (ring->space < 0)
		ring->space += ring->size;

	if (!dev->primary->master)
		return;

	master_priv = dev->primary->master->driver_priv;
	if (ring->head == ring->tail && master_priv->sarea_priv)
		master_priv->sarea_priv->perf_boxes |= I915_BOX_RING_EMPTY;
}