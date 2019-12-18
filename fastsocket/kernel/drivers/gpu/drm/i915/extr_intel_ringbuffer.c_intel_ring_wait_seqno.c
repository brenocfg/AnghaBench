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
struct intel_ring_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_retire_requests_ring (struct intel_ring_buffer*) ; 
 int i915_wait_seqno (struct intel_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_ring_wait_seqno(struct intel_ring_buffer *ring, u32 seqno)
{
	int ret;

	ret = i915_wait_seqno(ring, seqno);
	if (!ret)
		i915_gem_retire_requests_ring(ring);

	return ret;
}