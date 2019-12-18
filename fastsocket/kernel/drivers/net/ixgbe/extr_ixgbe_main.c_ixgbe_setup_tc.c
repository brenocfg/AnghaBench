#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  requested_mode; } ;
struct TYPE_7__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_3__ fc; TYPE_2__ mac; } ;
struct TYPE_6__ {scalar_t__ pg_tcs; } ;
struct TYPE_10__ {int pfc_mode_enable; TYPE_1__ num_tcs; } ;
struct TYPE_9__ {int pfc_mode_enable; } ;
struct ixgbe_adapter {TYPE_5__ dcb_cfg; TYPE_4__ temp_dcb_cfg; int /*<<< orphan*/  flags; int /*<<< orphan*/  last_lfc_mode; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IXGBE_FLAG_DCB_ENABLED ; 
 scalar_t__ MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  ixgbe_clear_interrupt_scheme (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_close (struct net_device*) ; 
 int /*<<< orphan*/  ixgbe_fc_none ; 
 int /*<<< orphan*/  ixgbe_init_interrupt_scheme (struct ixgbe_adapter*) ; 
 scalar_t__ ixgbe_mac_82598EB ; 
 int ixgbe_open (struct net_device*) ; 
 int /*<<< orphan*/  ixgbe_set_prio_tc_map (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_validate_rtr (struct ixgbe_adapter*,scalar_t__) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,scalar_t__) ; 
 scalar_t__ netif_running (struct net_device*) ; 

int ixgbe_setup_tc(struct net_device *dev, u8 tc)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);
	struct ixgbe_hw *hw = &adapter->hw;

	/* Hardware supports up to 8 traffic classes */
	if (tc > adapter->dcb_cfg.num_tcs.pg_tcs ||
	    (hw->mac.type == ixgbe_mac_82598EB &&
	     tc < MAX_TRAFFIC_CLASS))
		return -EINVAL;

	/* Hardware has to reinitialize queues and interrupts to
	 * match packet buffer alignment. Unfortunately, the
	 * hardware is not flexible enough to do this dynamically.
	 */
	if (netif_running(dev))
		ixgbe_close(dev);
	ixgbe_clear_interrupt_scheme(adapter);

#ifdef CONFIG_IXGBE_DCB
	if (tc) {
		netdev_set_num_tc(dev, tc);
		ixgbe_set_prio_tc_map(adapter);

		adapter->flags |= IXGBE_FLAG_DCB_ENABLED;

		if (adapter->hw.mac.type == ixgbe_mac_82598EB) {
			adapter->last_lfc_mode = adapter->hw.fc.requested_mode;
			adapter->hw.fc.requested_mode = ixgbe_fc_none;
		}
	} else {
		netdev_reset_tc(dev);

		if (adapter->hw.mac.type == ixgbe_mac_82598EB)
			adapter->hw.fc.requested_mode = adapter->last_lfc_mode;

		adapter->flags &= ~IXGBE_FLAG_DCB_ENABLED;

		adapter->temp_dcb_cfg.pfc_mode_enable = false;
		adapter->dcb_cfg.pfc_mode_enable = false;
	}

	ixgbe_validate_rtr(adapter, tc);

#endif /* CONFIG_IXGBE_DCB */
	ixgbe_init_interrupt_scheme(adapter);

	if (netif_running(dev))
		return ixgbe_open(dev);

	return 0;
}