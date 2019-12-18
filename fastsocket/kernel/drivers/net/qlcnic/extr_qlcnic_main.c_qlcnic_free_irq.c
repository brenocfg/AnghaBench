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
struct qlcnic_recv_context {struct qlcnic_host_tx_ring* sds_rings; } ;
struct qlcnic_host_tx_ring {scalar_t__ irq; } ;
struct qlcnic_host_sds_ring {scalar_t__ irq; } ;
struct qlcnic_adapter {int flags; int max_sds_rings; int max_drv_tx_rings; struct qlcnic_host_tx_ring* tx_ring; TYPE_1__* ahw; struct qlcnic_recv_context* recv_ctx; } ;
struct TYPE_2__ {scalar_t__ diag_test; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 int QLCNIC_TX_INTR_SHARED ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct qlcnic_host_tx_ring*) ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static void
qlcnic_free_irq(struct qlcnic_adapter *adapter)
{
	int ring;
	struct qlcnic_host_sds_ring *sds_ring;
	struct qlcnic_host_tx_ring *tx_ring;

	struct qlcnic_recv_context *recv_ctx = adapter->recv_ctx;

	if (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST) {
		if (qlcnic_82xx_check(adapter) ||
		    (qlcnic_83xx_check(adapter) &&
		     (adapter->flags & QLCNIC_MSIX_ENABLED))) {
			for (ring = 0; ring < adapter->max_sds_rings; ring++) {
				sds_ring = &recv_ctx->sds_rings[ring];
				free_irq(sds_ring->irq, sds_ring);
			}
		}
		if (qlcnic_83xx_check(adapter) &&
		    !(adapter->flags & QLCNIC_TX_INTR_SHARED)) {
			for (ring = 0; ring < adapter->max_drv_tx_rings;
			     ring++) {
				tx_ring = &adapter->tx_ring[ring];
				if (tx_ring->irq)
					free_irq(tx_ring->irq, tx_ring);
			}
		}
	}
}