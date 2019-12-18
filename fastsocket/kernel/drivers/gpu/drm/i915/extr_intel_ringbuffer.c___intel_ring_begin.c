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
struct intel_ring_buffer {scalar_t__ tail; scalar_t__ effective_size; int space; } ;

/* Variables and functions */
 int intel_wrap_ring_buffer (struct intel_ring_buffer*) ; 
 int ring_wait_for_space (struct intel_ring_buffer*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __intel_ring_begin(struct intel_ring_buffer *ring,
			      int bytes)
{
	int ret;

	if (unlikely(ring->tail + bytes > ring->effective_size)) {
		ret = intel_wrap_ring_buffer(ring);
		if (unlikely(ret))
			return ret;
	}

	if (unlikely(ring->space < bytes)) {
		ret = ring_wait_for_space(ring, bytes);
		if (unlikely(ret))
			return ret;
	}

	ring->space -= bytes;
	return 0;
}