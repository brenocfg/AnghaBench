#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {char* name; } ;
struct TYPE_8__ {int max_adj; int pps; void* enable; void* settime; void* gettime; void* adjtime; void* adjfreq; int /*<<< orphan*/  n_per_out; int /*<<< orphan*/  n_ext_ts; int /*<<< orphan*/  n_alarm; void* owner; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {TYPE_1__ mac; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/ * ptp_clock; TYPE_3__* pdev; TYPE_4__ ptp_caps; int /*<<< orphan*/  ptp_tx_work; int /*<<< orphan*/  tmreg_lock; TYPE_2__ hw; struct net_device* netdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 void* THIS_MODULE ; 
 int /*<<< orphan*/  __IXGBE_PTP_RUNNING ; 
 int /*<<< orphan*/  e_dev_err (char*) ; 
 int /*<<< orphan*/  e_dev_info (char*,char*) ; 
#define  ixgbe_mac_82599EB 129 
#define  ixgbe_mac_X540 128 
 void* ixgbe_ptp_adjfreq ; 
 void* ixgbe_ptp_adjtime ; 
 void* ixgbe_ptp_enable ; 
 void* ixgbe_ptp_gettime ; 
 int /*<<< orphan*/  ixgbe_ptp_reset (struct ixgbe_adapter*) ; 
 void* ixgbe_ptp_settime ; 
 int /*<<< orphan*/  ixgbe_ptp_tx_hwtstamp_work ; 
 int /*<<< orphan*/ * ptp_clock_register (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ixgbe_ptp_init(struct ixgbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	switch (adapter->hw.mac.type) {
	case ixgbe_mac_X540:
		snprintf(adapter->ptp_caps.name, 16, "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 1;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq;
		adapter->ptp_caps.adjtime = ixgbe_ptp_adjtime;
		adapter->ptp_caps.gettime = ixgbe_ptp_gettime;
		adapter->ptp_caps.settime = ixgbe_ptp_settime;
		adapter->ptp_caps.enable = ixgbe_ptp_enable;
		break;
	case ixgbe_mac_82599EB:
		snprintf(adapter->ptp_caps.name, 16, "%s", netdev->name);
		adapter->ptp_caps.owner = THIS_MODULE;
		adapter->ptp_caps.max_adj = 250000000;
		adapter->ptp_caps.n_alarm = 0;
		adapter->ptp_caps.n_ext_ts = 0;
		adapter->ptp_caps.n_per_out = 0;
		adapter->ptp_caps.pps = 0;
		adapter->ptp_caps.adjfreq = ixgbe_ptp_adjfreq;
		adapter->ptp_caps.adjtime = ixgbe_ptp_adjtime;
		adapter->ptp_caps.gettime = ixgbe_ptp_gettime;
		adapter->ptp_caps.settime = ixgbe_ptp_settime;
		adapter->ptp_caps.enable = ixgbe_ptp_enable;
		break;
	default:
		adapter->ptp_clock = NULL;
		return;
	}

	spin_lock_init(&adapter->tmreg_lock);
	INIT_WORK(&adapter->ptp_tx_work, ixgbe_ptp_tx_hwtstamp_work);

	adapter->ptp_clock = ptp_clock_register(&adapter->ptp_caps,
						&adapter->pdev->dev);
	if (IS_ERR(adapter->ptp_clock)) {
		adapter->ptp_clock = NULL;
		e_dev_err("ptp_clock_register failed\n");
	} else
		e_dev_info("registered PHC device on %s\n", netdev->name);

	ixgbe_ptp_reset(adapter);

	/* enter the IXGBE_PTP_RUNNING state */
	set_bit(__IXGBE_PTP_RUNNING, &adapter->state);

	return;
}