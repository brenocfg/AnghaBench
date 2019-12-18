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
struct intel_ring_buffer {scalar_t__ outstanding_lazy_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline u32 intel_ring_get_seqno(struct intel_ring_buffer *ring)
{
	BUG_ON(ring->outstanding_lazy_request == 0);
	return ring->outstanding_lazy_request;
}