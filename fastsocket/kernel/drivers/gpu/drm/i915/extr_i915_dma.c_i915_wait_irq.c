#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct intel_ring_buffer {int /*<<< orphan*/  (* irq_put ) (struct intel_ring_buffer*) ;int /*<<< orphan*/  irq_queue; scalar_t__ (* irq_get ) (struct intel_ring_buffer*) ;} ;
struct drm_i915_master_private {TYPE_3__* sarea_priv; } ;
struct drm_device {TYPE_2__* primary; scalar_t__ dev_private; } ;
struct TYPE_11__ {scalar_t__ counter; } ;
struct TYPE_12__ {TYPE_4__ dri1; } ;
typedef  TYPE_5__ drm_i915_private_t ;
struct TYPE_10__ {int last_dispatch; int /*<<< orphan*/  perf_boxes; } ;
struct TYPE_9__ {TYPE_1__* master; } ;
struct TYPE_8__ {struct drm_i915_master_private* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int DRM_HZ ; 
 int /*<<< orphan*/  DRM_WAIT_ON (int,int /*<<< orphan*/ ,int,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  I915_BOX_WAIT ; 
 struct intel_ring_buffer* LP_RING (TYPE_5__*) ; 
 int READ_BREADCRUMB (TYPE_5__*) ; 
 scalar_t__ stub1 (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct intel_ring_buffer*) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static int i915_wait_irq(struct drm_device * dev, int irq_nr)
{
	drm_i915_private_t *dev_priv = (drm_i915_private_t *) dev->dev_private;
	struct drm_i915_master_private *master_priv = dev->primary->master->driver_priv;
	int ret = 0;
	struct intel_ring_buffer *ring = LP_RING(dev_priv);

	DRM_DEBUG_DRIVER("irq_nr=%d breadcrumb=%d\n", irq_nr,
		  READ_BREADCRUMB(dev_priv));

	if (READ_BREADCRUMB(dev_priv) >= irq_nr) {
		if (master_priv->sarea_priv)
			master_priv->sarea_priv->last_dispatch = READ_BREADCRUMB(dev_priv);
		return 0;
	}

	if (master_priv->sarea_priv)
		master_priv->sarea_priv->perf_boxes |= I915_BOX_WAIT;

	if (ring->irq_get(ring)) {
		DRM_WAIT_ON(ret, ring->irq_queue, 3 * DRM_HZ,
			    READ_BREADCRUMB(dev_priv) >= irq_nr);
		ring->irq_put(ring);
	} else if (wait_for(READ_BREADCRUMB(dev_priv) >= irq_nr, 3000))
		ret = -EBUSY;

	if (ret == -EBUSY) {
		DRM_ERROR("EBUSY -- rec: %d emitted: %d\n",
			  READ_BREADCRUMB(dev_priv), (int)dev_priv->dri1.counter);
	}

	return ret;
}