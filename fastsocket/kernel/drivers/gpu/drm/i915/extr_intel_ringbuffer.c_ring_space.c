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
struct intel_ring_buffer {int head; int tail; scalar_t__ size; } ;

/* Variables and functions */
 int HEAD_ADDR ; 
 int I915_RING_FREE_SPACE ; 

__attribute__((used)) static inline int ring_space(struct intel_ring_buffer *ring)
{
	int space = (ring->head & HEAD_ADDR) - (ring->tail + I915_RING_FREE_SPACE);
	if (space < 0)
		space += ring->size;
	return space;
}