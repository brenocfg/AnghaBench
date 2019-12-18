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
typedef  void* u32 ;
struct ixgbe_ring {int /*<<< orphan*/  tail; void* next_to_alloc; void* next_to_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ixgbe_release_rx_desc(struct ixgbe_ring *rx_ring, u32 val)
{
	rx_ring->next_to_use = val;

	/* update next to alloc since we have filled the ring */
	rx_ring->next_to_alloc = val;
	/*
	 * Force memory writes to complete before letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable for weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();
	writel(val, rx_ring->tail);
}