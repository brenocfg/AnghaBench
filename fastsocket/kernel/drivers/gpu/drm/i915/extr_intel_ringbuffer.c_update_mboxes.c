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
struct intel_ring_buffer {int /*<<< orphan*/  outstanding_lazy_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  MI_LOAD_REGISTER_IMM (int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_mboxes(struct intel_ring_buffer *ring,
	      u32 mmio_offset)
{
	intel_ring_emit(ring, MI_LOAD_REGISTER_IMM(1));
	intel_ring_emit(ring, mmio_offset);
	intel_ring_emit(ring, ring->outstanding_lazy_request);
}