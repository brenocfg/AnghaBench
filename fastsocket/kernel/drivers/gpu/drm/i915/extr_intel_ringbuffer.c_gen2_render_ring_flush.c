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
struct intel_ring_buffer {int dummy; } ;

/* Variables and functions */
 int I915_GEM_DOMAIN_RENDER ; 
 int I915_GEM_DOMAIN_SAMPLER ; 
 int MI_FLUSH ; 
 int MI_NOOP ; 
 int MI_NO_WRITE_FLUSH ; 
 int MI_READ_FLUSH ; 
 int /*<<< orphan*/  intel_ring_advance (struct intel_ring_buffer*) ; 
 int intel_ring_begin (struct intel_ring_buffer*,int) ; 
 int /*<<< orphan*/  intel_ring_emit (struct intel_ring_buffer*,int) ; 

__attribute__((used)) static int
gen2_render_ring_flush(struct intel_ring_buffer *ring,
		       u32	invalidate_domains,
		       u32	flush_domains)
{
	u32 cmd;
	int ret;

	cmd = MI_FLUSH;
	if (((invalidate_domains|flush_domains) & I915_GEM_DOMAIN_RENDER) == 0)
		cmd |= MI_NO_WRITE_FLUSH;

	if (invalidate_domains & I915_GEM_DOMAIN_SAMPLER)
		cmd |= MI_READ_FLUSH;

	ret = intel_ring_begin(ring, 2);
	if (ret)
		return ret;

	intel_ring_emit(ring, cmd);
	intel_ring_emit(ring, MI_NOOP);
	intel_ring_advance(ring);

	return 0;
}