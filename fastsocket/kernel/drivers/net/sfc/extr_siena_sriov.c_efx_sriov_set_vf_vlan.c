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
typedef  int u8 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tci; } ;
struct efx_vf {int /*<<< orphan*/  status_lock; TYPE_1__ addr; } ;
struct efx_nic {int vf_init_count; struct efx_vf* vf; } ;

/* Variables and functions */
 int EINVAL ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  __efx_sriov_update_vf_addr (struct efx_vf*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 

int efx_sriov_set_vf_vlan(struct net_device *net_dev, int vf_i,
			  u16 vlan, u8 qos)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_vf *vf;
	u16 tci;

	if (vf_i >= efx->vf_init_count)
		return -EINVAL;
	vf = efx->vf + vf_i;

	mutex_lock(&vf->status_lock);
	tci = (vlan & VLAN_VID_MASK) | ((qos & 0x7) << VLAN_PRIO_SHIFT);
	vf->addr.tci = htons(tci);
	__efx_sriov_update_vf_addr(vf);
	mutex_unlock(&vf->status_lock);

	return 0;
}