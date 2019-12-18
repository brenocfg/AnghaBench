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
struct intel_ring_buffer {struct drm_i915_gem_object* private; } ;
struct drm_i915_gem_object {int gtt_offset; } ;

/* Variables and functions */
 int BLT_DEPTH_32 ; 
 int BLT_ROP_GXCOPY ; 
 int DIV_ROUND_UP (int,int) ; 
 int ENOSPC ; 
 int I830_BATCH_LIMIT ; 
 unsigned int I915_DISPATCH_PINNED ; 
 unsigned int I915_DISPATCH_SECURE ; 
 int MI_BATCH_BUFFER ; 
 int MI_BATCH_NON_SECURE ; 
 int MI_FLUSH ; 
 int MI_NOOP ; 
 int XY_SRC_COPY_BLT_CMD ; 
 int XY_SRC_COPY_BLT_WRITE_ALPHA ; 
 int XY_SRC_COPY_BLT_WRITE_RGB ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 

__attribute__((used)) static int
i830_dispatch_execbuffer(struct intel_ring_buffer *ring,
				u32 offset, u32 len,
				unsigned flags)
{
	int ret;

	if (flags & I915_DISPATCH_PINNED) {
		ret = intel_ring_begin(ring, 4);
		if (ret)
			return ret;

		intel_ring_emit(ring, MI_BATCH_BUFFER);
		intel_ring_emit(ring, offset | (flags & I915_DISPATCH_SECURE ? 0 : MI_BATCH_NON_SECURE));
		intel_ring_emit(ring, offset + len - 8);
		intel_ring_emit(ring, MI_NOOP);
		intel_ring_advance(ring);
	} else {
		struct drm_i915_gem_object *obj = ring->private;
		u32 cs_offset = obj->gtt_offset;

		if (len > I830_BATCH_LIMIT)
			return -ENOSPC;

		ret = intel_ring_begin(ring, 9+3);
		if (ret)
			return ret;
		/* Blit the batch (which has now all relocs applied) to the stable batch
		 * scratch bo area (so that the CS never stumbles over its tlb
		 * invalidation bug) ... */
		intel_ring_emit(ring, XY_SRC_COPY_BLT_CMD |
				XY_SRC_COPY_BLT_WRITE_ALPHA |
				XY_SRC_COPY_BLT_WRITE_RGB);
		intel_ring_emit(ring, BLT_DEPTH_32 | BLT_ROP_GXCOPY | 4096);
		intel_ring_emit(ring, 0);
		intel_ring_emit(ring, (DIV_ROUND_UP(len, 4096) << 16) | 1024);
		intel_ring_emit(ring, cs_offset);
		intel_ring_emit(ring, 0);
		intel_ring_emit(ring, 4096);
		intel_ring_emit(ring, offset);
		intel_ring_emit(ring, MI_FLUSH);

		/* ... and execute it. */
		intel_ring_emit(ring, MI_BATCH_BUFFER);
		intel_ring_emit(ring, cs_offset | (flags & I915_DISPATCH_SECURE ? 0 : MI_BATCH_NON_SECURE));
		intel_ring_emit(ring, cs_offset + len - 8);
		intel_ring_advance(ring);
	}

	return 0;
}