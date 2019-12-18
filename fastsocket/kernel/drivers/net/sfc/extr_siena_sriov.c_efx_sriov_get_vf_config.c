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
typedef  int u16 ;
struct net_device {int dummy; } ;
struct ifla_vf_info {int vf; int vlan; int qos; scalar_t__ tx_rate; int /*<<< orphan*/  mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  tci; int /*<<< orphan*/  mac_addr; } ;
struct efx_vf {TYPE_1__ addr; } ;
struct efx_nic {int vf_init_count; struct efx_vf* vf; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

int efx_sriov_get_vf_config(struct net_device *net_dev, int vf_i,
			    struct ifla_vf_info *ivi)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = efx->vf + vf_i;

	ivi->vf = vf_i;
	memcpy(ivi->mac, vf->addr.mac_addr, ETH_ALEN);
	ivi->tx_rate = 0;
	tci = ntohs(vf->addr.tci);
	ivi->vlan = tci & VLAN_VID_MASK;
	ivi->qos = (tci >> VLAN_PRIO_SHIFT) & 0x7;

	return 0;
}