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
struct intel_ring_buffer {int /*<<< orphan*/  mmio_base; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  drm_i915_private_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GEN6_BSD_RNCID ; 
 int GEN6_BSD_SLEEP_INDICATOR ; 
 int /*<<< orphan*/  GEN6_BSD_SLEEP_MSG_DISABLE ; 
 int /*<<< orphan*/  GEN6_BSD_SLEEP_PSMI_CONTROL ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  I915_WRITE_TAIL (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_TAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for (int,int) ; 

__attribute__((used)) static void gen6_bsd_ring_write_tail(struct intel_ring_buffer *ring,
				     u32 value)
{
	drm_i915_private_t *dev_priv = ring->dev->dev_private;

       /* Every tail move must follow the sequence below */

	/* Disable notification that the ring is IDLE. The GT
	 * will then assume that it is busy and bring it out of rc6.
	 */
	I915_WRITE(GEN6_BSD_SLEEP_PSMI_CONTROL,
		   _MASKED_BIT_ENABLE(GEN6_BSD_SLEEP_MSG_DISABLE));

	/* Clear the context id. Here be magic! */
	I915_WRITE64(GEN6_BSD_RNCID, 0x0);

	/* Wait for the ring not to be idle, i.e. for it to wake up. */
	if (wait_for((I915_READ(GEN6_BSD_SLEEP_PSMI_CONTROL) &
		      GEN6_BSD_SLEEP_INDICATOR) == 0,
		     50))
		DRM_ERROR("timed out waiting for the BSD ring to wake up\n");

	/* Now that the ring is fully powered up, update the tail */
	I915_WRITE_TAIL(ring, value);
	POSTING_READ(RING_TAIL(ring->mmio_base));

	/* Let the ring send IDLE messages to the GT again,
	 * and so let it sleep to conserve power when idle.
	 */
	I915_WRITE(GEN6_BSD_SLEEP_PSMI_CONTROL,
		   _MASKED_BIT_DISABLE(GEN6_BSD_SLEEP_MSG_DISABLE));
}