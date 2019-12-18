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
struct netxen_adapter {scalar_t__ is_up; } ;

/* Variables and functions */
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  netxen_free_hw_resources (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_free_sw_resources (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_napi_del (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_nic_free_irq (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_release_rx_buffers (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_remove_sysfs_entries (struct netxen_adapter*) ; 

__attribute__((used)) static void
netxen_nic_detach(struct netxen_adapter *adapter)
{
	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return;

	netxen_remove_sysfs_entries(adapter);

	netxen_free_hw_resources(adapter);
	netxen_release_rx_buffers(adapter);
	netxen_nic_free_irq(adapter);
	netxen_napi_del(adapter);
	netxen_free_sw_resources(adapter);

	adapter->is_up = 0;
}