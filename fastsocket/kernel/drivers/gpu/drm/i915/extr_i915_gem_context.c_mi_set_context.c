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
typedef  int u32 ;
struct intel_ring_buffer {int (* flush ) (struct intel_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; scalar_t__ itlb_before_ctx_switch; } ;
struct i915_hw_context {TYPE_1__* obj; } ;
struct TYPE_2__ {int gtt_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_GEM_GPU_DOMAINS ; 
 scalar_t__ IS_GEN6 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_GEN7 (int /*<<< orphan*/ ) ; 
 int MI_ARB_DISABLE ; 
 int MI_ARB_ENABLE ; 
 int MI_ARB_ON_OFF ; 
 int MI_MM_SPACE_GTT ; 
 int MI_NOOP ; 
 int MI_RESTORE_EXT_STATE_EN ; 
 int MI_SAVE_EXT_STATE_EN ; 
 int MI_SET_CONTEXT ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 
 int stub1 (struct intel_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
mi_set_context(struct intel_ring_buffer *ring,
	       struct i915_hw_context *new_context,
	       u32 hw_flags)
{
	int ret;

	/* w/a: If Flush TLB Invalidation Mode is enabled, driver must do a TLB
	 * invalidation prior to MI_SET_CONTEXT. On GEN6 we don't set the value
	 * explicitly, so we rely on the value at ring init, stored in
	 * itlb_before_ctx_switch.
	 */
	if (IS_GEN6(ring->dev) && ring->itlb_before_ctx_switch) {
		ret = ring->flush(ring, I915_GEM_GPU_DOMAINS, 0);
		if (ret)
			return ret;
	}

	ret = intel_ring_begin(ring, 6);
	if (ret)
		return ret;

	if (IS_GEN7(ring->dev))
		intel_ring_emit(ring, MI_ARB_ON_OFF | MI_ARB_DISABLE);
	else
		intel_ring_emit(ring, MI_NOOP);

	intel_ring_emit(ring, MI_NOOP);
	intel_ring_emit(ring, MI_SET_CONTEXT);
	intel_ring_emit(ring, new_context->obj->gtt_offset |
			MI_MM_SPACE_GTT |
			MI_SAVE_EXT_STATE_EN |
			MI_RESTORE_EXT_STATE_EN |
			hw_flags);
	/* w/a: MI_SET_CONTEXT must always be followed by MI_NOOP */
	intel_ring_emit(ring, MI_NOOP);

	if (IS_GEN7(ring->dev))
		intel_ring_emit(ring, MI_ARB_ON_OFF | MI_ARB_ENABLE);
	else
		intel_ring_emit(ring, MI_NOOP);

	intel_ring_advance(ring);

	return ret;
}