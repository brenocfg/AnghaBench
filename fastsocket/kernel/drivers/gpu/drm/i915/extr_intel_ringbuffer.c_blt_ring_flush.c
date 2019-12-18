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
typedef  int uint32_t ;
typedef  int u32 ;
struct intel_ring_buffer {int dummy; } ;

/* Variables and functions */
 int I915_GEM_DOMAIN_RENDER ; 
 int I915_GEM_HWS_SCRATCH_ADDR ; 
 int MI_FLUSH_DW ; 
 int MI_FLUSH_DW_OP_STOREDW ; 
 int MI_FLUSH_DW_STORE_INDEX ; 
 int MI_FLUSH_DW_USE_GTT ; 
 int MI_INVALIDATE_TLB ; 
 int MI_NOOP ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 

__attribute__((used)) static int blt_ring_flush(struct intel_ring_buffer *ring,
			  u32 invalidate, u32 flush)
{
	uint32_t cmd;
	int ret;

	ret = intel_ring_begin(ring, 4);
	if (ret)
		return ret;

	cmd = MI_FLUSH_DW;
	/*
	 * Bspec vol 1c.3 - blitter engine command streamer:
	 * "If ENABLED, all TLBs will be invalidated once the flush
	 * operation is complete. This bit is only valid when the
	 * Post-Sync Operation field is a value of 1h or 3h."
	 */
	if (invalidate & I915_GEM_DOMAIN_RENDER)
		cmd |= MI_INVALIDATE_TLB | MI_FLUSH_DW_STORE_INDEX |
			MI_FLUSH_DW_OP_STOREDW;
	intel_ring_emit(ring, cmd);
	intel_ring_emit(ring, I915_GEM_HWS_SCRATCH_ADDR | MI_FLUSH_DW_USE_GTT);
	intel_ring_emit(ring, 0);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_advance(ring);
	return 0;
}