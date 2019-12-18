#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fnum; } ;
struct qlcnic_adapter {scalar_t__ is_up; int /*<<< orphan*/  tx_clean_lock; int /*<<< orphan*/  flags; TYPE_3__ fhash; TYPE_2__* ahw; int /*<<< orphan*/  state; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ linkup; TYPE_1__* sriov; } ;
struct TYPE_4__ {int /*<<< orphan*/  bc; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  QLCNIC_FW_LRO_MSS_CAP ; 
 int /*<<< orphan*/  QLCNIC_NIU_NON_PROMISC_MODE ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_delete_lb_filters (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_mac_list (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_fw_destroy_ctx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_napi_disable (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_nic_set_promisc (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_release_tx_buffers (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_reset_rx_buffers_list (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup_async_list (int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __qlcnic_down(struct qlcnic_adapter *adapter, struct net_device *netdev)
{
	if (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		return;

	if (!test_and_clear_bit(__QLCNIC_DEV_UP, &adapter->state))
		return;

	if (qlcnic_sriov_vf_check(adapter))
		qlcnic_sriov_cleanup_async_list(&adapter->ahw->sriov->bc);
	smp_mb();
	spin_lock(&adapter->tx_clean_lock);
	netif_carrier_off(netdev);
	adapter->ahw->linkup = 0;
	netif_tx_disable(netdev);

	qlcnic_free_mac_list(adapter);

	if (adapter->fhash.fnum)
		qlcnic_delete_lb_filters(adapter);

	qlcnic_nic_set_promisc(adapter, QLCNIC_NIU_NON_PROMISC_MODE);

	qlcnic_napi_disable(adapter);

	qlcnic_fw_destroy_ctx(adapter);
	adapter->flags &= ~QLCNIC_FW_LRO_MSS_CAP;

	qlcnic_reset_rx_buffers_list(adapter);
	qlcnic_release_tx_buffers(adapter);
	spin_unlock(&adapter->tx_clean_lock);
}