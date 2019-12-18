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
struct TYPE_5__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_time_us; int /*<<< orphan*/  rx_time_us; } ;
struct TYPE_6__ {TYPE_1__ data; } ;
struct TYPE_7__ {TYPE_2__ normal; } ;
struct TYPE_8__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ is_up; TYPE_3__ coal; TYPE_4__ ahw; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; int /*<<< orphan*/  rx_coalesce_usecs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int netxen_get_intr_coalesce(struct net_device *netdev,
			struct ethtool_coalesce *ethcoal)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);

	if (!NX_IS_REVISION_P3(adapter->ahw.revision_id))
		return -EINVAL;

	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return -EINVAL;

	ethcoal->rx_coalesce_usecs = adapter->coal.normal.data.rx_time_us;
	ethcoal->tx_coalesce_usecs = adapter->coal.normal.data.tx_time_us;
	ethcoal->rx_max_coalesced_frames =
		adapter->coal.normal.data.rx_packets;
	ethcoal->tx_max_coalesced_frames =
		adapter->coal.normal.data.tx_packets;

	return 0;
}