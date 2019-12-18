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
struct intel_ring_buffer {int tail; int size; int /*<<< orphan*/  (* write_tail ) (struct intel_ring_buffer*,int) ;TYPE_1__* dev; } ;
struct TYPE_4__ {int stop_rings; } ;
struct drm_i915_private {TYPE_2__ gpu_error; } ;
struct TYPE_3__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int intel_ring_flag (struct intel_ring_buffer*) ; 
 int /*<<< orphan*/  stub1 (struct intel_ring_buffer*,int) ; 

void intel_ring_advance(struct intel_ring_buffer *ring)
{
	struct drm_i915_private *dev_priv = ring->dev->dev_private;

	ring->tail &= ring->size - 1;
	if (dev_priv->gpu_error.stop_rings & intel_ring_flag(ring))
		return;
	ring->write_tail(ring, ring->tail);
}