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
 scalar_t__ I915_NUM_RINGS ; 

__attribute__((used)) static inline u32
intel_ring_sync_index(struct intel_ring_buffer *ring,
		      struct intel_ring_buffer *other)
{
	int idx;

	/*
	 * cs -> 0 = vcs, 1 = bcs
	 * vcs -> 0 = bcs, 1 = cs,
	 * bcs -> 0 = cs, 1 = vcs.
	 */

	idx = (other - ring) - 1;
	if (idx < 0)
		idx += I915_NUM_RINGS;

	return idx;
}