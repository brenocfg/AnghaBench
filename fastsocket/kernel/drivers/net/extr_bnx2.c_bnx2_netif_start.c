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
struct bnx2 {int /*<<< orphan*/  phy_lock; int /*<<< orphan*/  dev; scalar_t__ link_up; int /*<<< orphan*/  intr_sem; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2_cnic_start (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_enable_int (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_napi_enable (struct bnx2*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_netif_start(struct bnx2 *bp, bool start_cnic)
{
	if (atomic_dec_and_test(&bp->intr_sem)) {
		if (netif_running(bp->dev)) {
			netif_tx_wake_all_queues(bp->dev);
			spin_lock_bh(&bp->phy_lock);
			if (bp->link_up)
				netif_carrier_on(bp->dev);
			spin_unlock_bh(&bp->phy_lock);
			bnx2_napi_enable(bp);
			bnx2_enable_int(bp);
			if (start_cnic)
				bnx2_cnic_start(bp);
		}
	}
}