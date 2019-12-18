#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_ring_buffer {struct drm_i915_gem_object* last_context_obj; } ;
struct i915_hw_context {int is_initialized; struct drm_i915_gem_object* obj; struct intel_ring_buffer* ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_domains; } ;
struct drm_i915_gem_object {scalar_t__ pin_count; int dirty; TYPE_1__ base; struct intel_ring_buffer* ring; int /*<<< orphan*/  cache_level; int /*<<< orphan*/  has_global_gtt_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CONTEXT_ALIGN ; 
 int /*<<< orphan*/  I915_GEM_DOMAIN_INSTRUCTION ; 
 int /*<<< orphan*/  MI_FORCE_RESTORE ; 
 int /*<<< orphan*/  MI_RESTORE_INHIBIT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  drm_gem_object_reference (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference (TYPE_1__*) ; 
 int /*<<< orphan*/  i915_gem_gtt_bind_object (struct drm_i915_gem_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_object_move_to_active (struct drm_i915_gem_object*,struct intel_ring_buffer*) ; 
 int i915_gem_object_pin (struct drm_i915_gem_object*,int /*<<< orphan*/ ,int,int) ; 
 int i915_gem_object_set_to_gtt_domain (struct drm_i915_gem_object*,int) ; 
 int /*<<< orphan*/  i915_gem_object_unpin (struct drm_i915_gem_object*) ; 
 scalar_t__ is_default_context (struct i915_hw_context*) ; 
 int mi_set_context (struct intel_ring_buffer*,struct i915_hw_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_switch(struct i915_hw_context *to)
{
	struct intel_ring_buffer *ring = to->ring;
	struct drm_i915_gem_object *from_obj = ring->last_context_obj;
	u32 hw_flags = 0;
	int ret;

	BUG_ON(from_obj != NULL && from_obj->pin_count == 0);

	if (from_obj == to->obj)
		return 0;

	ret = i915_gem_object_pin(to->obj, CONTEXT_ALIGN, false, false);
	if (ret)
		return ret;

	/* Clear this page out of any CPU caches for coherent swap-in/out. Note
	 * that thanks to write = false in this call and us not setting any gpu
	 * write domains when putting a context object onto the active list
	 * (when switching away from it), this won't block.
	 * XXX: We need a real interface to do this instead of trickery. */
	ret = i915_gem_object_set_to_gtt_domain(to->obj, false);
	if (ret) {
		i915_gem_object_unpin(to->obj);
		return ret;
	}

	if (!to->obj->has_global_gtt_mapping)
		i915_gem_gtt_bind_object(to->obj, to->obj->cache_level);

	if (!to->is_initialized || is_default_context(to))
		hw_flags |= MI_RESTORE_INHIBIT;
	else if (WARN_ON_ONCE(from_obj == to->obj)) /* not yet expected */
		hw_flags |= MI_FORCE_RESTORE;

	ret = mi_set_context(ring, to, hw_flags);
	if (ret) {
		i915_gem_object_unpin(to->obj);
		return ret;
	}

	/* The backing object for the context is done after switching to the
	 * *next* context. Therefore we cannot retire the previous context until
	 * the next context has already started running. In fact, the below code
	 * is a bit suboptimal because the retiring can occur simply after the
	 * MI_SET_CONTEXT instead of when the next seqno has completed.
	 */
	if (from_obj != NULL) {
		from_obj->base.read_domains = I915_GEM_DOMAIN_INSTRUCTION;
		i915_gem_object_move_to_active(from_obj, ring);
		/* As long as MI_SET_CONTEXT is serializing, ie. it flushes the
		 * whole damn pipeline, we don't need to explicitly mark the
		 * object dirty. The only exception is that the context must be
		 * correct in case the object gets swapped out. Ideally we'd be
		 * able to defer doing this until we know the object would be
		 * swapped, but there is no way to do that yet.
		 */
		from_obj->dirty = 1;
		BUG_ON(from_obj->ring != ring);
		i915_gem_object_unpin(from_obj);

		drm_gem_object_unreference(&from_obj->base);
	}

	drm_gem_object_reference(&to->obj->base);
	ring->last_context_obj = to->obj;
	to->is_initialized = true;

	return 0;
}