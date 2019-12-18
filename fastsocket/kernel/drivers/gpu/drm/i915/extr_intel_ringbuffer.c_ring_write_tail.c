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
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring_buffer {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WRITE_TAIL (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ring_write_tail(struct intel_ring_buffer *ring,
			    u32 value)
{
	drm_i915_private_t *dev_priv = ring->dev->dev_private;
	I915_WRITE_TAIL(ring, value);
}