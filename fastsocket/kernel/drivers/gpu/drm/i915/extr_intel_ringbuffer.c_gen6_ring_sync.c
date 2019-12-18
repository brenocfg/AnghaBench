#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct intel_ring_buffer {int* semaphore_register; size_t id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MI_NOOP ; 
 int MI_SEMAPHORE_COMPARE ; 
 int MI_SEMAPHORE_MBOX ; 
 int MI_SEMAPHORE_REGISTER ; 
 int MI_SEMAPHORE_SYNC_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  i915_gem_has_seqno_wrapped (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
gen6_ring_sync(struct intel_ring_buffer *waiter,
	       struct intel_ring_buffer *signaller,
	       u32 seqno)
{
	int ret;
	u32 dw1 = MI_SEMAPHORE_MBOX |
		  MI_SEMAPHORE_COMPARE |
		  MI_SEMAPHORE_REGISTER;

	/* Throughout all of the GEM code, seqno passed implies our current
	 * seqno is >= the last seqno executed. However for hardware the
	 * comparison is strictly greater than.
	 */
	seqno -= 1;

	WARN_ON(signaller->semaphore_register[waiter->id] ==
		MI_SEMAPHORE_SYNC_INVALID);

	ret = intel_ring_begin(waiter, 4);
	if (ret)
		return ret;

	/* If seqno wrap happened, omit the wait with no-ops */
	if (likely(!i915_gem_has_seqno_wrapped(waiter->dev, seqno))) {
		intel_ring_emit(waiter,
				dw1 |
				signaller->semaphore_register[waiter->id]);
		intel_ring_emit(waiter, seqno);
		intel_ring_emit(waiter, 0);
		intel_ring_emit(waiter, MI_NOOP);
	} else {
		intel_ring_emit(waiter, MI_NOOP);
		intel_ring_emit(waiter, MI_NOOP);
		intel_ring_emit(waiter, MI_NOOP);
		intel_ring_emit(waiter, MI_NOOP);
	}
	intel_ring_advance(waiter);

	return 0;
}