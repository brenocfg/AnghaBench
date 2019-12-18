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
struct TYPE_6__ {int rx_time_us; int rx_packets; int tx_time_us; int tx_packets; } ;
struct TYPE_7__ {TYPE_2__ data; } ;
struct TYPE_8__ {TYPE_3__ normal; scalar_t__ flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ is_up; TYPE_4__ coal; TYPE_1__ ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int rx_coalesce_usecs; int rx_max_coalesced_frames; int tx_coalesce_usecs; int tx_max_coalesced_frames; scalar_t__ tx_max_coalesced_frames_high; scalar_t__ tx_coalesce_usecs_high; scalar_t__ rx_max_coalesced_frames_high; scalar_t__ rx_coalesce_usecs_high; scalar_t__ pkt_rate_high; scalar_t__ tx_max_coalesced_frames_low; scalar_t__ tx_coalesce_usecs_low; scalar_t__ rx_max_coalesced_frames_low; scalar_t__ rx_coalesce_usecs_low; scalar_t__ pkt_rate_low; scalar_t__ use_adaptive_tx_coalesce; scalar_t__ use_adaptive_rx_coalesce; scalar_t__ stats_block_coalesce_usecs; scalar_t__ tx_max_coalesced_frames_irq; scalar_t__ tx_coalesce_usecs_irq; scalar_t__ rx_max_coalesced_frames_irq; scalar_t__ rx_coalesce_usecs_irq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 int NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS ; 
 int NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US ; 
 scalar_t__ NETXEN_NIC_INTR_DEFAULT ; 
 int /*<<< orphan*/  NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netxen_config_intr_coalesce (struct netxen_adapter*) ; 

__attribute__((used)) static int netxen_set_intr_coalesce(struct net_device *netdev,
			struct ethtool_coalesce *ethcoal)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);

	if (!NX_IS_REVISION_P3(adapter->ahw.revision_id))
		return -EINVAL;

	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return -EINVAL;

	/*
	* Return Error if unsupported values or
	* unsupported parameters are set.
	*/
	if (ethcoal->rx_coalesce_usecs > 0xffff ||
		ethcoal->rx_max_coalesced_frames > 0xffff ||
		ethcoal->tx_coalesce_usecs > 0xffff ||
		ethcoal->tx_max_coalesced_frames > 0xffff ||
		ethcoal->rx_coalesce_usecs_irq ||
		ethcoal->rx_max_coalesced_frames_irq ||
		ethcoal->tx_coalesce_usecs_irq ||
		ethcoal->tx_max_coalesced_frames_irq ||
		ethcoal->stats_block_coalesce_usecs ||
		ethcoal->use_adaptive_rx_coalesce ||
		ethcoal->use_adaptive_tx_coalesce ||
		ethcoal->pkt_rate_low ||
		ethcoal->rx_coalesce_usecs_low ||
		ethcoal->rx_max_coalesced_frames_low ||
		ethcoal->tx_coalesce_usecs_low ||
		ethcoal->tx_max_coalesced_frames_low ||
		ethcoal->pkt_rate_high ||
		ethcoal->rx_coalesce_usecs_high ||
		ethcoal->rx_max_coalesced_frames_high ||
		ethcoal->tx_coalesce_usecs_high ||
		ethcoal->tx_max_coalesced_frames_high)
		return -EINVAL;

	if (!ethcoal->rx_coalesce_usecs ||
		!ethcoal->rx_max_coalesced_frames) {
		adapter->coal.flags = NETXEN_NIC_INTR_DEFAULT;
		adapter->coal.normal.data.rx_time_us =
			NETXEN_DEFAULT_INTR_COALESCE_RX_TIME_US;
		adapter->coal.normal.data.rx_packets =
			NETXEN_DEFAULT_INTR_COALESCE_RX_PACKETS;
	} else {
		adapter->coal.flags = 0;
		adapter->coal.normal.data.rx_time_us =
		ethcoal->rx_coalesce_usecs;
		adapter->coal.normal.data.rx_packets =
		ethcoal->rx_max_coalesced_frames;
	}
	adapter->coal.normal.data.tx_time_us = ethcoal->tx_coalesce_usecs;
	adapter->coal.normal.data.tx_packets =
	ethcoal->tx_max_coalesced_frames;

	netxen_config_intr_coalesce(adapter);

	return 0;
}