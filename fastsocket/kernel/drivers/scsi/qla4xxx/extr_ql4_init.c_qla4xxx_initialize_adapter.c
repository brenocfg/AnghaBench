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
struct scsi_qla_host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  flags; TYPE_1__* isp_ops; scalar_t__ eeprom_cmd_data; } ;
struct TYPE_2__ {int (* start_firmware ) (struct scsi_qla_host*) ;int (* get_sys_info ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* disable_intrs ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* pci_config ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_ONLINE ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA_ERROR ; 
 int RESET_ADAPTER ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla80XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  qla4_83xx_enable_mbox_intrs (struct scsi_qla_host*) ; 
 int qla4xxx_about_firmware (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_build_ddb_list (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  qla4xxx_free_irqs (struct scsi_qla_host*) ; 
 int qla4xxx_init_firmware (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_init_local_data (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 
 int stub3 (struct scsi_qla_host*) ; 
 int stub4 (struct scsi_qla_host*) ; 

int qla4xxx_initialize_adapter(struct scsi_qla_host *ha, int is_reset)
{
	int status = QLA_ERROR;

	ha->eeprom_cmd_data = 0;

	ql4_printk(KERN_INFO, ha, "Configuring PCI space...\n");
	ha->isp_ops->pci_config(ha);

	ha->isp_ops->disable_intrs(ha);

	/* Initialize the Host adapter request/response queues and firmware */
	if (ha->isp_ops->start_firmware(ha) == QLA_ERROR)
		goto exit_init_hba;

	/*
	 * For ISP83XX, mailbox and IOCB interrupts are enabled separately.
	 * Mailbox interrupts must be enabled prior to issuing any mailbox
	 * command in order to prevent the possibility of losing interrupts
	 * while switching from polling to interrupt mode. IOCB interrupts are
	 * enabled via isp_ops->enable_intrs.
	 */
	if (is_qla8032(ha))
		qla4_83xx_enable_mbox_intrs(ha);

	if (qla4xxx_about_firmware(ha) == QLA_ERROR)
		goto exit_init_hba;

	if (ha->isp_ops->get_sys_info(ha) == QLA_ERROR)
		goto exit_init_hba;

	qla4xxx_init_local_data(ha);

	status = qla4xxx_init_firmware(ha);
	if (status == QLA_ERROR)
		goto exit_init_hba;

	if (is_reset == RESET_ADAPTER)
		qla4xxx_build_ddb_list(ha, is_reset);

	set_bit(AF_ONLINE, &ha->flags);
exit_init_hba:
	if (is_qla80XX(ha) && (status == QLA_ERROR)) {
		/* Since interrupts are registered in start_firmware for
		 * 80XX, release them here if initialize_adapter fails */
		qla4xxx_free_irqs(ha);
	}

	DEBUG2(printk("scsi%ld: initialize adapter: %s\n", ha->host_no,
	    status == QLA_ERROR ? "FAILED" : "SUCCEEDED"));
	return status;
}