#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pci_channel_io_perm_failure; } ;
struct qla_hw_data {TYPE_2__* isp_ops; TYPE_1__ flags; int /*<<< orphan*/  pdev; } ;
struct TYPE_9__ {struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* disable_intrs ) (struct qla_hw_data*) ;} ;

/* Variables and functions */
 scalar_t__ pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla24xx_reset_risc (TYPE_3__*) ; 
 int /*<<< orphan*/  qla25xx_manipulate_risc_semaphore (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*) ; 

void
qla24xx_reset_chip(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;

	if (pci_channel_offline(ha->pdev) &&
	    ha->flags.pci_channel_io_perm_failure) {
		return;
	}

	ha->isp_ops->disable_intrs(ha);

	qla25xx_manipulate_risc_semaphore(vha);

	/* Perform RISC reset. */
	qla24xx_reset_risc(vha);
}