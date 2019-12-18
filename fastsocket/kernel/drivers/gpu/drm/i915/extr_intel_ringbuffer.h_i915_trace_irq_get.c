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
typedef  scalar_t__ u32 ;
struct intel_ring_buffer {scalar_t__ trace_irq_seqno; scalar_t__ (* irq_get ) (struct intel_ring_buffer*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct intel_ring_buffer*) ; 

__attribute__((used)) static inline void i915_trace_irq_get(struct intel_ring_buffer *ring, u32 seqno)
{
	if (ring->trace_irq_seqno == 0 && ring->irq_get(ring))
		ring->trace_irq_seqno = seqno;
}