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
struct ixgbe_ring {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  __IXGBE_RX_FCOE ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int ixgbe_rx_pg_order(struct ixgbe_ring *ring)
{
#ifdef IXGBE_FCOE
	if (test_bit(__IXGBE_RX_FCOE, &ring->state))
		return (PAGE_SIZE < 8192) ? 1 : 0;
#endif
	return 0;
}