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
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring_buffer {int outstanding_lazy_request; int /*<<< orphan*/ * signal_mbox; } ;

/* Variables and functions */
 int I915_GEM_HWS_INDEX ; 
 int MI_STORE_DWORD_INDEX ; 
 int MI_STORE_DWORD_INDEX_SHIFT ; 
 int MI_USER_INTERRUPT ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  update_mboxes (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gen6_add_request(struct intel_ring_buffer *ring)
{
	u32 mbox1_reg;
	u32 mbox2_reg;
	int ret;

	ret = intel_ring_begin(ring, 10);
	if (ret)
		return ret;

	mbox1_reg = ring->signal_mbox[0];
	mbox2_reg = ring->signal_mbox[1];

	update_mboxes(ring, mbox1_reg);
	update_mboxes(ring, mbox2_reg);
	intel_ring_emit(ring, MI_STORE_DWORD_INDEX);
	intel_ring_emit(ring, I915_GEM_HWS_INDEX << MI_STORE_DWORD_INDEX_SHIFT);
	intel_ring_emit(ring, ring->outstanding_lazy_request);
	intel_ring_emit(ring, MI_USER_INTERRUPT);
	intel_ring_advance(ring);

	return 0;
}