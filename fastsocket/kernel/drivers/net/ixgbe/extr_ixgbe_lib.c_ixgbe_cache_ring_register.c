#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_adapter {TYPE_2__** tx_ring; TYPE_1__** rx_ring; } ;
struct TYPE_4__ {scalar_t__ reg_idx; } ;
struct TYPE_3__ {scalar_t__ reg_idx; } ;

/* Variables and functions */
 scalar_t__ ixgbe_cache_ring_dcb (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_cache_ring_dcb_sriov (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_cache_ring_rss (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_cache_ring_sriov (struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_cache_ring_register(struct ixgbe_adapter *adapter)
{
	/* start with default case */
	adapter->rx_ring[0]->reg_idx = 0;
	adapter->tx_ring[0]->reg_idx = 0;

#ifdef CONFIG_IXGBE_DCB
	if (ixgbe_cache_ring_dcb_sriov(adapter))
		return;

	if (ixgbe_cache_ring_dcb(adapter))
		return;

#endif
	if (ixgbe_cache_ring_sriov(adapter))
		return;

	ixgbe_cache_ring_rss(adapter);
}