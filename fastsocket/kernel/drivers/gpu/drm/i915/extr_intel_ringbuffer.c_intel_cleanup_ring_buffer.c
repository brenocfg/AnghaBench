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
struct intel_ring_buffer {int /*<<< orphan*/  (* cleanup ) (struct intel_ring_buffer*) ;TYPE_2__* obj; int /*<<< orphan*/  virtual_start; int /*<<< orphan*/  name; TYPE_1__* dev; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_CTL (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_status_page (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (TYPE_2__*) ; 
 int intel_ring_idle (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct intel_ring_buffer*) ; 

void intel_cleanup_ring_buffer(struct intel_ring_buffer *ring)
{
	struct drm_i915_private *dev_priv;
	int ret;

	if (ring->obj == NULL)
		return;

	/* Disable the ring buffer. The ring must be idle at this point */
	dev_priv = ring->dev->dev_private;
	ret = intel_ring_idle(ring);
	if (ret)
		DRM_ERROR("failed to quiesce %s whilst cleaning up: %d\n",
			  ring->name, ret);

	I915_WRITE_CTL(ring, 0);

	iounmap(ring->virtual_start);

	i915_gem_object_unpin(ring->obj);
	drm_gem_object_unreference(&ring->obj->base);
	ring->obj = NULL;

	if (ring->cleanup)
		ring->cleanup(ring);

	cleanup_status_page(ring);
}