#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pci_channel_io_perm_failure; } ;
struct qla_hw_data {TYPE_2__* isp_ops; TYPE_1__ flags; int /*<<< orphan*/  pdev; } ;
struct TYPE_8__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* enable_intrs ) (struct qla_hw_data*) ;int /*<<< orphan*/  (* disable_intrs ) (struct qla_hw_data*) ;} ;

/* Variables and functions */
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlafx00_soc_cpu_reset (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  stub2 (struct qla_hw_data*) ; 
 scalar_t__ unlikely (int) ; 

void
qlafx00_soft_reset(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (unlikely(pci_channel_offline(ha->pdev) &&
	    ha->flags.pci_channel_io_perm_failure))
		return;

	ha->isp_ops->disable_intrs(ha);
	qlafx00_soc_cpu_reset(vha);
	ha->isp_ops->enable_intrs(ha);
}