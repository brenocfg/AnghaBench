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
struct net_device {int dummy; } ;
struct TYPE_9__ {int eee_disable; } ;
struct TYPE_10__ {TYPE_4__ _82575; } ;
struct TYPE_7__ {scalar_t__ media_type; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_5__ dev_spec; TYPE_2__ phy; TYPE_1__ mac; } ;
struct igb_adapter {TYPE_3__* pdev; struct e1000_hw hw; } ;
struct ethtool_eee {scalar_t__ tx_lpi_enabled; scalar_t__ advertised; scalar_t__ eee_enabled; scalar_t__ tx_lpi_timer; } ;
typedef  int s32 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ e1000_i350 ; 
 scalar_t__ e1000_media_type_copper ; 
 int igb_get_eee (struct net_device*,struct ethtool_eee*) ; 
 int /*<<< orphan*/  igb_reinit_locked (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_reset (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_set_eee_i350 (struct e1000_hw*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int igb_set_eee(struct net_device *netdev,
		       struct ethtool_eee *edata)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct ethtool_eee eee_curr;
	s32 ret_val;

	if ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_copper))
		return -EOPNOTSUPP;

	ret_val = igb_get_eee(netdev, &eee_curr);
	if (ret_val)
		return ret_val;

	if (eee_curr.eee_enabled) {
		if (eee_curr.tx_lpi_enabled != edata->tx_lpi_enabled) {
			dev_err(&adapter->pdev->dev,
				"Setting EEE tx-lpi is not supported\n");
			return -EINVAL;
		}

		/* Tx LPI timer is not implemented currently */
		if (edata->tx_lpi_timer) {
			dev_err(&adapter->pdev->dev,
				"Setting EEE Tx LPI timer is not supported\n");
			return -EINVAL;
		}

		if (eee_curr.advertised != edata->advertised) {
			dev_err(&adapter->pdev->dev,
				"Setting EEE Advertisement is not supported\n");
			return -EINVAL;
		}

	} else if (!edata->eee_enabled) {
		dev_err(&adapter->pdev->dev,
			"Setting EEE options are not supported with EEE disabled\n");
			return -EINVAL;
		}

	if (hw->dev_spec._82575.eee_disable != !edata->eee_enabled) {
		hw->dev_spec._82575.eee_disable = !edata->eee_enabled;
		igb_set_eee_i350(hw);

		/* reset link */
		if (netif_running(netdev))
			igb_reinit_locked(adapter);
		else
			igb_reset(adapter);
	}

	return 0;
}