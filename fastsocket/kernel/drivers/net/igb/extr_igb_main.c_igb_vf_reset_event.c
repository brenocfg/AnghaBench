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
struct igb_adapter {TYPE_1__* vf_data; } ;
struct TYPE_2__ {unsigned char* vf_mac_addresses; int flags; } ;

/* Variables and functions */
 int IGB_VF_FLAG_PF_SET_MAC ; 
 int /*<<< orphan*/  eth_random_addr (unsigned char*) ; 
 int /*<<< orphan*/  igb_vf_reset (struct igb_adapter*,size_t) ; 

__attribute__((used)) static void igb_vf_reset_event(struct igb_adapter *adapter, u32 vf)
{
	unsigned char *vf_mac = adapter->vf_data[vf].vf_mac_addresses;

	/* generate a new mac address as we were hotplug removed/added */
	if (!(adapter->vf_data[vf].flags & IGB_VF_FLAG_PF_SET_MAC))
		eth_random_addr(vf_mac);

	/* process remaining reset events */
	igb_vf_reset(adapter, vf);
}