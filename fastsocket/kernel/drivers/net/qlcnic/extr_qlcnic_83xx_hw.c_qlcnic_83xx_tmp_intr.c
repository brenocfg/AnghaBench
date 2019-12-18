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
struct qlcnic_host_sds_ring {struct qlcnic_adapter* adapter; } ;
struct qlcnic_adapter {int flags; TYPE_2__* ahw; TYPE_1__* nic_ops; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  diag_cnt; } ;
struct TYPE_3__ {scalar_t__ (* clear_legacy_intr ) (struct qlcnic_adapter*) ;} ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int QLCNIC_MSIX_ENABLED ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_intr (struct qlcnic_adapter*,struct qlcnic_host_sds_ring*) ; 
 scalar_t__ stub1 (struct qlcnic_adapter*) ; 

irqreturn_t qlcnic_83xx_tmp_intr(int irq, void *data)
{
	struct qlcnic_host_sds_ring *sds_ring = data;
	struct qlcnic_adapter *adapter = sds_ring->adapter;

	if (adapter->flags & QLCNIC_MSIX_ENABLED)
		goto done;

	if (adapter->nic_ops->clear_legacy_intr(adapter) == IRQ_NONE)
		return IRQ_NONE;

done:
	adapter->ahw->diag_cnt++;
	qlcnic_83xx_enable_intr(adapter, sds_ring);

	return IRQ_HANDLED;
}