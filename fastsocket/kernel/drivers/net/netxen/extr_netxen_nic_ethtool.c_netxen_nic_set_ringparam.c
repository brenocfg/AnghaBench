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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ port_type; int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ num_rxd; scalar_t__ num_txd; scalar_t__ num_jumbo_rxd; TYPE_1__ ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_jumbo_pending; int /*<<< orphan*/  rx_pending; scalar_t__ rx_mini_pending; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MAX_CMD_DESCRIPTORS ; 
 scalar_t__ MAX_JUMBO_RCV_DESCRIPTORS_10G ; 
 scalar_t__ MAX_RCV_DESCRIPTORS_10G ; 
 scalar_t__ MAX_RCV_DESCRIPTORS_1G ; 
 int /*<<< orphan*/  MIN_CMD_DESCRIPTORS ; 
 int /*<<< orphan*/  MIN_JUMBO_DESCRIPTORS ; 
 int /*<<< orphan*/  MIN_RCV_DESCRIPTORS ; 
 scalar_t__ NETXEN_NIC_GBE ; 
 scalar_t__ NX_IS_REVISION_P2 (int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int netxen_nic_reset_context (struct netxen_adapter*) ; 
 scalar_t__ netxen_validate_ringparam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static int
netxen_nic_set_ringparam(struct net_device *dev,
		struct ethtool_ringparam *ring)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u16 max_rcv_desc = MAX_RCV_DESCRIPTORS_10G;
	u16 max_jumbo_desc = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	u16 num_rxd, num_jumbo_rxd, num_txd;

	if (NX_IS_REVISION_P2(adapter->ahw.revision_id))
		return -EOPNOTSUPP;

	if (ring->rx_mini_pending)
		return -EOPNOTSUPP;

	if (adapter->ahw.port_type == NETXEN_NIC_GBE) {
		max_rcv_desc = MAX_RCV_DESCRIPTORS_1G;
		max_jumbo_desc = MAX_JUMBO_RCV_DESCRIPTORS_10G;
	}

	num_rxd = netxen_validate_ringparam(ring->rx_pending,
			MIN_RCV_DESCRIPTORS, max_rcv_desc, "rx");

	num_jumbo_rxd = netxen_validate_ringparam(ring->rx_jumbo_pending,
			MIN_JUMBO_DESCRIPTORS, max_jumbo_desc, "rx jumbo");

	num_txd = netxen_validate_ringparam(ring->tx_pending,
			MIN_CMD_DESCRIPTORS, MAX_CMD_DESCRIPTORS, "tx");

	if (num_rxd == adapter->num_rxd && num_txd == adapter->num_txd &&
			num_jumbo_rxd == adapter->num_jumbo_rxd)
		return 0;

	adapter->num_rxd = num_rxd;
	adapter->num_jumbo_rxd = num_jumbo_rxd;
	adapter->num_txd = num_txd;

	return netxen_nic_reset_context(adapter);
}