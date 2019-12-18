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
struct net_device {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; TYPE_1__* vf_data; } ;
struct ifla_vf_info {int vf; int /*<<< orphan*/  qos; int /*<<< orphan*/  vlan; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  pf_qos; int /*<<< orphan*/  pf_vlan; int /*<<< orphan*/  tx_rate; int /*<<< orphan*/  vf_mac_addresses; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_ndo_get_vf_config(struct net_device *netdev,
				 int vf, struct ifla_vf_info *ivi)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	if (vf >= adapter->vfs_allocated_count)
		return -EINVAL;
	ivi->vf = vf;
	memcpy(&ivi->mac, adapter->vf_data[vf].vf_mac_addresses, ETH_ALEN);
	ivi->tx_rate = adapter->vf_data[vf].tx_rate;
	ivi->vlan = adapter->vf_data[vf].pf_vlan;
	ivi->qos = adapter->vf_data[vf].pf_qos;
	return 0;
}