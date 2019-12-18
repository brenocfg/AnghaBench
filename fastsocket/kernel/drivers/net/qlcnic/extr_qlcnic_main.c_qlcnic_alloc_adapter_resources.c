#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_recv_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_time_us; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_time_us; int /*<<< orphan*/  type; int /*<<< orphan*/  flag; } ;
struct qlcnic_hardware_context {TYPE_2__ coal; } ;
struct qlcnic_adapter {int /*<<< orphan*/  stats; TYPE_1__* pdev; int /*<<< orphan*/  recv_ctx; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QLCNIC_DEF_INTR_COALESCE_RX_PACKETS ; 
 int /*<<< orphan*/  QLCNIC_DEF_INTR_COALESCE_RX_TIME_US ; 
 int /*<<< orphan*/  QLCNIC_DEF_INTR_COALESCE_TX_PACKETS ; 
 int /*<<< orphan*/  QLCNIC_DEF_INTR_COALESCE_TX_TIME_US ; 
 int /*<<< orphan*/  QLCNIC_INTR_COAL_TYPE_RX ; 
 int /*<<< orphan*/  QLCNIC_INTR_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_alloc_adapter_resources(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err = 0;

	adapter->recv_ctx = kzalloc(sizeof(struct qlcnic_recv_context),
				GFP_KERNEL);
	if (!adapter->recv_ctx) {
		dev_err(&adapter->pdev->dev,
			"Failed to allocate recv ctx resources for adapter\n");
		err = -ENOMEM;
		goto err_out;
	}
	/* Initialize interrupt coalesce parameters */
	ahw->coal.flag = QLCNIC_INTR_DEFAULT;
	ahw->coal.type = QLCNIC_INTR_COAL_TYPE_RX;
	ahw->coal.rx_time_us = QLCNIC_DEF_INTR_COALESCE_RX_TIME_US;
	ahw->coal.rx_packets = QLCNIC_DEF_INTR_COALESCE_RX_PACKETS;
	if (qlcnic_83xx_check(adapter)) {
		ahw->coal.tx_time_us = QLCNIC_DEF_INTR_COALESCE_TX_TIME_US;
		ahw->coal.tx_packets = QLCNIC_DEF_INTR_COALESCE_TX_PACKETS;
	}
	/* clear stats */
	memset(&adapter->stats, 0, sizeof(adapter->stats));
err_out:
	return err;
}