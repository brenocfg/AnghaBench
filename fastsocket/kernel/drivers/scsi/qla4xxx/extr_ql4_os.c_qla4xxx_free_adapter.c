#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_qla_host {TYPE_4__* isp_ops; scalar_t__ task_wq; scalar_t__ dpc_thread; scalar_t__ timer_active; TYPE_3__* qla4_83xx_reg; TYPE_2__* qla4_82xx_reg; TYPE_1__* reg; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* idc_unlock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_lock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* reset_firmware ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* disable_intrs ) (struct scsi_qla_host*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  risc_intr; } ;
struct TYPE_6__ {int /*<<< orphan*/  host_int; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_SCSI_PROCESSOR_INTR ; 
 int DID_NO_CONNECT ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla80XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_8xxx_clear_drv_active (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_abort_active_cmds (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  qla4xxx_free_irqs (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_mem_free (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_stop_timer (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_rmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub4 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla4xxx_free_adapter(struct scsi_qla_host *ha)
{
	qla4xxx_abort_active_cmds(ha, DID_NO_CONNECT << 16);

	/* Turn-off interrupts on the card. */
	ha->isp_ops->disable_intrs(ha);

	if (is_qla40XX(ha)) {
		writel(set_rmask(CSR_SCSI_PROCESSOR_INTR),
		       &ha->reg->ctrl_status);
		readl(&ha->reg->ctrl_status);
	} else if (is_qla8022(ha)) {
		writel(0, &ha->qla4_82xx_reg->host_int);
		readl(&ha->qla4_82xx_reg->host_int);
	} else if (is_qla8032(ha)) {
		writel(0, &ha->qla4_83xx_reg->risc_intr);
		readl(&ha->qla4_83xx_reg->risc_intr);
	}

	/* Remove timer thread, if present */
	if (ha->timer_active)
		qla4xxx_stop_timer(ha);

	/* Kill the kernel thread for this host */
	if (ha->dpc_thread)
		destroy_workqueue(ha->dpc_thread);

	/* Kill the kernel thread for this host */
	if (ha->task_wq)
		destroy_workqueue(ha->task_wq);

	/* Put firmware in known state */
	ha->isp_ops->reset_firmware(ha);

	if (is_qla80XX(ha)) {
		ha->isp_ops->idc_lock(ha);
		qla4_8xxx_clear_drv_active(ha);
		ha->isp_ops->idc_unlock(ha);
	}

	/* Detach interrupts */
	qla4xxx_free_irqs(ha);

	/* free extra memory */
	qla4xxx_mem_free(ha);
}