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
struct qlcnic_adapter {int max_drv_tx_rings; int flags; TYPE_1__* ahw; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {scalar_t__ diag_test; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_LOOPBACK_TEST ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  __QLCNIC_FW_ATTACHED ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_config_intrpt (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_fw_cmd_del_rx_ctx (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_fw_cmd_del_tx_ctx (struct qlcnic_adapter*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_fw_destroy_ctx(struct qlcnic_adapter *adapter)
{
	int ring;

	if (test_and_clear_bit(__QLCNIC_FW_ATTACHED, &adapter->state)) {
		qlcnic_fw_cmd_del_rx_ctx(adapter);
		for (ring = 0; ring < adapter->max_drv_tx_rings; ring++)
			qlcnic_fw_cmd_del_tx_ctx(adapter,
						 &adapter->tx_ring[ring]);

		if (qlcnic_83xx_check(adapter) &&
		    (adapter->flags & QLCNIC_MSIX_ENABLED)) {
			if (adapter->ahw->diag_test != QLCNIC_LOOPBACK_TEST)
				qlcnic_83xx_config_intrpt(adapter, 0);
		}
		/* Allow dma queues to drain after context reset */
		msleep(20);
	}
}