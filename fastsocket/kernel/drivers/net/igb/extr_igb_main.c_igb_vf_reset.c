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
typedef  size_t u32 ;
struct igb_adapter {int /*<<< orphan*/  netdev; TYPE_1__* vf_data; } ;
struct TYPE_2__ {scalar_t__ num_vf_mc_hashes; int /*<<< orphan*/  pf_qos; scalar_t__ pf_vlan; int /*<<< orphan*/  last_nack; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_VF_FLAG_PF_SET_MAC ; 
 int /*<<< orphan*/  igb_clear_vf_vfta (struct igb_adapter*,size_t) ; 
 int /*<<< orphan*/  igb_ndo_set_vf_vlan (int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_set_rx_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_set_vmolr (struct igb_adapter*,size_t,int) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void igb_vf_reset(struct igb_adapter *adapter, u32 vf)
{
	/* clear flags - except flag that indicates PF has set the MAC */
	adapter->vf_data[vf].flags &= IGB_VF_FLAG_PF_SET_MAC;
	adapter->vf_data[vf].last_nack = jiffies;

	/* reset offloads to defaults */
	igb_set_vmolr(adapter, vf, true);

	/* reset vlans for device */
	igb_clear_vf_vfta(adapter, vf);
	if (adapter->vf_data[vf].pf_vlan)
		igb_ndo_set_vf_vlan(adapter->netdev, vf,
				    adapter->vf_data[vf].pf_vlan,
				    adapter->vf_data[vf].pf_qos);
	else
		igb_clear_vf_vfta(adapter, vf);

	/* reset multicast table array for vf */
	adapter->vf_data[vf].num_vf_mc_hashes = 0;

	/* Flush and reset the mta with the new values */
	igb_set_rx_mode(adapter->netdev);
}