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
typedef  scalar_t__ uint32_t ;
struct intel_ring_buffer {int gpu_caches_dirty; int (* flush ) (struct intel_ring_buffer*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ I915_GEM_GPU_DOMAINS ; 
 int stub1 (struct intel_ring_buffer*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_i915_gem_ring_flush (struct intel_ring_buffer*,scalar_t__,scalar_t__) ; 

int
intel_ring_invalidate_all_caches(struct intel_ring_buffer *ring)
{
	uint32_t flush_domains;
	int ret;

	flush_domains = 0;
	if (ring->gpu_caches_dirty)
		flush_domains = I915_GEM_GPU_DOMAINS;

	ret = ring->flush(ring, I915_GEM_GPU_DOMAINS, flush_domains);
	if (ret)
		return ret;

	trace_i915_gem_ring_flush(ring, I915_GEM_GPU_DOMAINS, flush_domains);

	ring->gpu_caches_dirty = false;
	return 0;
}