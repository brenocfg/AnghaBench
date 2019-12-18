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
struct TYPE_2__ {int /*<<< orphan*/  revision_id; } ;
struct netxen_adapter {scalar_t__ is_up; int capabilities; int /*<<< orphan*/  tx_clean_lock; int /*<<< orphan*/  (* set_promisc ) (struct netxen_adapter*,int /*<<< orphan*/ ) ;TYPE_1__ ahw; int /*<<< orphan*/  (* stop_port ) (struct netxen_adapter*) ;int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NETXEN_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  NETXEN_NIU_NON_PROMISC_MODE ; 
 int NX_FW_CAPABILITY_LINK_NOTIFICATION ; 
 scalar_t__ NX_IS_REVISION_P3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __NX_DEV_UP ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netxen_linkevent_request (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_napi_disable (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_p3_free_mac_list (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_release_tx_buffers (struct netxen_adapter*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct netxen_adapter*) ; 
 int /*<<< orphan*/  stub2 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__netxen_nic_down(struct netxen_adapter *adapter, struct net_device *netdev)
{
	if (adapter->is_up != NETXEN_ADAPTER_UP_MAGIC)
		return;

	if (!test_and_clear_bit(__NX_DEV_UP, &adapter->state))
		return;

	smp_mb();
	spin_lock(&adapter->tx_clean_lock);
	netif_carrier_off(netdev);
	netif_tx_disable(netdev);

	if (adapter->capabilities & NX_FW_CAPABILITY_LINK_NOTIFICATION)
		netxen_linkevent_request(adapter, 0);

	if (adapter->stop_port)
		adapter->stop_port(adapter);

	if (NX_IS_REVISION_P3(adapter->ahw.revision_id))
		netxen_p3_free_mac_list(adapter);

	adapter->set_promisc(adapter, NETXEN_NIU_NON_PROMISC_MODE);

	netxen_napi_disable(adapter);

	netxen_release_tx_buffers(adapter);
	spin_unlock(&adapter->tx_clean_lock);
}