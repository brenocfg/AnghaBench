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
struct intel_ring_buffer {int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  (* get_seqno ) (struct intel_ring_buffer*,int) ;int /*<<< orphan*/ * obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  hangcheck_timer; scalar_t__ hangcheck_count; } ;
struct drm_i915_private {TYPE_1__ gpu_error; } ;
struct drm_device {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 scalar_t__ DRM_I915_HANGCHECK_JIFFIES ; 
 scalar_t__ i915_enable_hangcheck ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_up (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  trace_i915_gem_request_complete (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void notify_ring(struct drm_device *dev,
			struct intel_ring_buffer *ring)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (ring->obj == NULL)
		return;

	trace_i915_gem_request_complete(ring, ring->get_seqno(ring, false));

	wake_up_all(&ring->irq_queue);
	if (i915_enable_hangcheck) {
		dev_priv->gpu_error.hangcheck_count = 0;
		mod_timer(&dev_priv->gpu_error.hangcheck_timer,
			  round_jiffies_up(jiffies + DRM_I915_HANGCHECK_JIFFIES));
	}
}