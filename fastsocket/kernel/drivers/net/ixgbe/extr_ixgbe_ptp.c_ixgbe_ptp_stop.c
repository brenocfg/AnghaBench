#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ixgbe_adapter {TYPE_1__* netdev; int /*<<< orphan*/ * ptp_clock; int /*<<< orphan*/ * ptp_tx_skb; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  flags2; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_FLAG2_PTP_PPS_ENABLED ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_dev_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ptp_setup_sdp (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbe_ptp_stop(struct ixgbe_adapter *adapter)
{
	/* Leave the IXGBE_PTP_RUNNING state. */
	if (!test_and_clear_bit(__IXGBE_PTP_RUNNING, &adapter->state))
		return;

	/* stop the PPS signal */
	adapter->flags2 &= ~IXGBE_FLAG2_PTP_PPS_ENABLED;
	ixgbe_ptp_setup_sdp(adapter);

	cancel_work_sync(&adapter->ptp_tx_work);
	if (adapter->ptp_tx_skb) {
		dev_kfree_skb_any(adapter->ptp_tx_skb);
		adapter->ptp_tx_skb = NULL;
	}

	if (adapter->ptp_clock) {
		ptp_clock_unregister(adapter->ptp_clock);
		adapter->ptp_clock = NULL;
		e_dev_info("removed PHC on %s\n",
			   adapter->netdev->name);
	}
}