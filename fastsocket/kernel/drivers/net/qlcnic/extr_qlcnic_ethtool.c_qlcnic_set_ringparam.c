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
typedef  scalar_t__ u16 ;
struct qlcnic_adapter {scalar_t__ num_rxd; scalar_t__ num_txd; scalar_t__ num_jumbo_rxd; int /*<<< orphan*/  max_jumbo_rxd; int /*<<< orphan*/  max_rxd; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAX_CMD_DESCRIPTORS ; 
 int /*<<< orphan*/  MIN_CMD_DESCRIPTORS ; 
 int /*<<< orphan*/  MIN_JUMBO_DESCRIPTORS ; 
 int /*<<< orphan*/  MIN_RCV_DESCRIPTORS ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int qlcnic_reset_context (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_validate_ringparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
qlcnic_set_ringparam(struct net_device *dev,
		struct ethtool_ringparam *ring)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	u16 num_rxd, num_jumbo_rxd, num_txd;

	if (ring->rx_mini_pending)
		return -EOPNOTSUPP;

	num_rxd = qlcnic_validate_ringparam(ring->rx_pending,
			MIN_RCV_DESCRIPTORS, adapter->max_rxd, "rx");

	num_jumbo_rxd = qlcnic_validate_ringparam(ring->rx_jumbo_pending,
			MIN_JUMBO_DESCRIPTORS, adapter->max_jumbo_rxd,
						"rx jumbo");

	num_txd = qlcnic_validate_ringparam(ring->tx_pending,
			MIN_CMD_DESCRIPTORS, MAX_CMD_DESCRIPTORS, "tx");

	if (num_rxd == adapter->num_rxd && num_txd == adapter->num_txd &&
			num_jumbo_rxd == adapter->num_jumbo_rxd)
		return 0;

	adapter->num_rxd = num_rxd;
	adapter->num_jumbo_rxd = num_jumbo_rxd;
	adapter->num_txd = num_txd;

	return qlcnic_reset_context(adapter);
}