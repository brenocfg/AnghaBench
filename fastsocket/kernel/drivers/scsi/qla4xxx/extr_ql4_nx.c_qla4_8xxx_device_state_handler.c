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
typedef  size_t uint32_t ;
struct scsi_qla_host {unsigned long nx_dev_init_timeout; TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* idc_unlock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_lock ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 size_t MAX_STATES ; 
 int /*<<< orphan*/  QLA8XXX_CRB_DEV_STATE ; 
#define  QLA8XXX_DEV_COLD 134 
#define  QLA8XXX_DEV_FAILED 133 
#define  QLA8XXX_DEV_INITIALIZING 132 
#define  QLA8XXX_DEV_NEED_QUIESCENT 131 
#define  QLA8XXX_DEV_NEED_RESET 130 
#define  QLA8XXX_DEV_QUIESCENT 129 
#define  QLA8XXX_DEV_READY 128 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  is_qla8022 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  is_qla8032 (struct scsi_qla_host*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 char** qdev_state ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,size_t,...) ; 
 int /*<<< orphan*/  ql4xdontresethba ; 
 int /*<<< orphan*/  qla4_82xx_need_reset_handler (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_need_reset_handler (struct scsi_qla_host*) ; 
 int qla4_8xxx_device_bootstrap (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_8xxx_need_qsnt_handler (struct scsi_qla_host*) ; 
 size_t qla4_8xxx_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla4_8xxx_update_idc_reg (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_8xxx_wr_direct (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qla4xxx_dead_adapter_cleanup (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub10 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub11 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub12 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub4 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub5 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub6 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub7 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub8 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub9 (struct scsi_qla_host*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int qla4_8xxx_device_state_handler(struct scsi_qla_host *ha)
{
	uint32_t dev_state;
	int rval = QLA_SUCCESS;
	unsigned long dev_init_timeout;

	rval = qla4_8xxx_update_idc_reg(ha);
	if (rval == QLA_ERROR)
		goto exit_state_handler;

	dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
	DEBUG2(ql4_printk(KERN_INFO, ha, "Device state is 0x%x = %s\n",
			  dev_state, dev_state < MAX_STATES ?
			  qdev_state[dev_state] : "Unknown"));

	/* wait for 30 seconds for device to go ready */
	dev_init_timeout = jiffies + (ha->nx_dev_init_timeout * HZ);

	ha->isp_ops->idc_lock(ha);
	while (1) {

		if (time_after_eq(jiffies, dev_init_timeout)) {
			ql4_printk(KERN_WARNING, ha,
				   "%s: Device Init Failed 0x%x = %s\n",
				   DRIVER_NAME,
				   dev_state, dev_state < MAX_STATES ?
				   qdev_state[dev_state] : "Unknown");
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
		}

		dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
		ql4_printk(KERN_INFO, ha, "Device state is 0x%x = %s\n",
			   dev_state, dev_state < MAX_STATES ?
			   qdev_state[dev_state] : "Unknown");

		/* NOTE: Make sure idc unlocked upon exit of switch statement */
		switch (dev_state) {
		case QLA8XXX_DEV_READY:
			goto exit;
		case QLA8XXX_DEV_COLD:
			rval = qla4_8xxx_device_bootstrap(ha);
			goto exit;
		case QLA8XXX_DEV_INITIALIZING:
			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);
			break;
		case QLA8XXX_DEV_NEED_RESET:
			/*
			 * For ISP8324, if NEED_RESET is set by any driver,
			 * it should be honored, irrespective of IDC_CTRL
			 * DONTRESET_BIT0
			 */
			if (is_qla8032(ha)) {
				qla4_83xx_need_reset_handler(ha);
			} else if (is_qla8022(ha)) {
				if (!ql4xdontresethba) {
					qla4_82xx_need_reset_handler(ha);
					/* Update timeout value after need
					 * reset handler */
					dev_init_timeout = jiffies +
						(ha->nx_dev_init_timeout * HZ);
				} else {
					ha->isp_ops->idc_unlock(ha);
					msleep(1000);
					ha->isp_ops->idc_lock(ha);
				}
			}
			break;
		case QLA8XXX_DEV_NEED_QUIESCENT:
			/* idc locked/unlocked in handler */
			qla4_8xxx_need_qsnt_handler(ha);
			break;
		case QLA8XXX_DEV_QUIESCENT:
			ha->isp_ops->idc_unlock(ha);
			msleep(1000);
			ha->isp_ops->idc_lock(ha);
			break;
		case QLA8XXX_DEV_FAILED:
			ha->isp_ops->idc_unlock(ha);
			qla4xxx_dead_adapter_cleanup(ha);
			rval = QLA_ERROR;
			ha->isp_ops->idc_lock(ha);
			goto exit;
		default:
			ha->isp_ops->idc_unlock(ha);
			qla4xxx_dead_adapter_cleanup(ha);
			rval = QLA_ERROR;
			ha->isp_ops->idc_lock(ha);
			goto exit;
		}
	}
exit:
	ha->isp_ops->idc_unlock(ha);
exit_state_handler:
	return rval;
}