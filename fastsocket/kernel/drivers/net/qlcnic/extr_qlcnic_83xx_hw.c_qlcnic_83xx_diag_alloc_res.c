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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct qlcnic_host_sds_ring {int dummy; } ;
struct qlcnic_host_rds_ring {int dummy; } ;
struct qlcnic_adapter {scalar_t__ is_up; int max_sds_rings; size_t max_rds_rings; int flags; int /*<<< orphan*/  state; TYPE_3__* ahw; TYPE_1__* recv_ctx; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int diag_test; TYPE_2__* hw_ops; scalar_t__ loopback_state; scalar_t__ linkup; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setup_link_event ) (struct qlcnic_adapter*,int) ;} ;
struct TYPE_4__ {struct qlcnic_host_sds_ring* sds_rings; struct qlcnic_host_rds_ring* rds_rings; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int QLCNIC_INTERRUPT_TEST ; 
 int QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  __QLCNIC_DEV_UP ; 
 int /*<<< orphan*/  __qlcnic_down (struct qlcnic_adapter*,struct net_device*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_attach (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 int /*<<< orphan*/  qlcnic_83xx_free_mbx_intr (struct qlcnic_adapter*) ; 
 int qlcnic_attach (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_detach (struct qlcnic_adapter*) ; 
 int qlcnic_fw_create_ctx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_post_rx_buffers (struct qlcnic_adapter*,struct qlcnic_host_rds_ring*,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static int qlcnic_83xx_diag_alloc_res(struct net_device *netdev, int test,
				      int num_sds_ring)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_rds_ring *rds_ring;
	u16 adapter_state = adapter->is_up;
	u8 ring;
	int ret;

	netif_device_detach(netdev);

	if (netif_running(netdev))
		__qlcnic_down(adapter, netdev);

	qlcnic_detach(adapter);

	adapter->max_sds_rings = 1;
	adapter->ahw->diag_test = test;
	adapter->ahw->linkup = 0;

	ret = qlcnic_attach(adapter);
	if (ret) {
		netif_device_attach(netdev);
		return ret;
	}

	ret = qlcnic_fw_create_ctx(adapter);
	if (ret) {
		qlcnic_detach(adapter);
		if (adapter_state == QLCNIC_ADAPTER_UP_MAGIC) {
			adapter->max_sds_rings = num_sds_ring;
			qlcnic_attach(adapter);
		}
		netif_device_attach(netdev);
		return ret;
	}

	for (ring = 0; ring < adapter->max_rds_rings; ring++) {
		rds_ring = &adapter->recv_ctx->rds_rings[ring];
		qlcnic_post_rx_buffers(adapter, rds_ring, ring);
	}

	if (adapter->ahw->diag_test == QLCNIC_INTERRUPT_TEST) {
		for (ring = 0; ring < adapter->max_sds_rings; ring++) {
			sds_ring = &adapter->recv_ctx->sds_rings[ring];
			qlcnic_83xx_enable_intr(adapter, sds_ring);
		}
	}

	if (adapter->ahw->diag_test == QLCNIC_LOOPBACK_TEST) {
		/* disable and free mailbox interrupt */
		if (!(adapter->flags & QLCNIC_MSIX_ENABLED))
			qlcnic_83xx_free_mbx_intr(adapter);
		adapter->ahw->loopback_state = 0;
		adapter->ahw->hw_ops->setup_link_event(adapter, 1);
	}

	set_bit(__QLCNIC_DEV_UP, &adapter->state);
	return 0;
}