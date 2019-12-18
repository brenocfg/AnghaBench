#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/  quiesce_owner; int /*<<< orphan*/  nic_core_reset_owner; } ;
struct qla_hw_data {unsigned long fcoe_dev_init_timeout; TYPE_2__ flags; } ;
struct TYPE_12__ {int /*<<< orphan*/  init_done; } ;
struct TYPE_14__ {TYPE_1__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;

/* Variables and functions */
 unsigned long HZ ; 
 int MAX_STATES ; 
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
#define  QLA8XXX_DEV_COLD 134 
#define  QLA8XXX_DEV_FAILED 133 
#define  QLA8XXX_DEV_INITIALIZING 132 
#define  QLA8XXX_DEV_NEED_QUIESCENT 131 
#define  QLA8XXX_DEV_NEED_RESET 130 
#define  QLA8XXX_DEV_QUIESCENT 129 
#define  QLA8XXX_DEV_READY 128 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 char* qdev_state (int) ; 
 int /*<<< orphan*/  ql2xdontresethba ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int qla82xx_device_bootstrap (TYPE_3__*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_need_qsnt_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  qla82xx_need_reset_handler (TYPE_3__*) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_set_drv_active (TYPE_3__*) ; 
 int /*<<< orphan*/  qla82xx_set_idc_version (TYPE_3__*) ; 
 int /*<<< orphan*/  qla8xxx_dev_failed_handler (TYPE_3__*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

int
qla82xx_device_state_handler(scsi_qla_host_t *vha)
{
	uint32_t dev_state;
	uint32_t old_dev_state;
	int rval = QLA_SUCCESS;
	unsigned long dev_init_timeout;
	struct qla_hw_data *ha = vha->hw;
	int loopcount = 0;

	qla82xx_idc_lock(ha);
	if (!vha->flags.init_done) {
		qla82xx_set_drv_active(vha);
		qla82xx_set_idc_version(vha);
	}

	dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	old_dev_state = dev_state;
	ql_log(ql_log_info, vha, 0x009b,
	    "Device state is 0x%x = %s.\n",
	    dev_state,
	    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");

	/* wait for 30 seconds for device to go ready */
	dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout * HZ);

	while (1) {

		if (time_after_eq(jiffies, dev_init_timeout)) {
			ql_log(ql_log_fatal, vha, 0x009c,
			    "Device init failed.\n");
			rval = QLA_FUNCTION_FAILED;
			break;
		}
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
		if (old_dev_state != dev_state) {
			loopcount = 0;
			old_dev_state = dev_state;
		}
		if (loopcount < 5) {
			ql_log(ql_log_info, vha, 0x009d,
			    "Device state is 0x%x = %s.\n",
			    dev_state,
			    dev_state < MAX_STATES ? qdev_state(dev_state) :
			    "Unknown");
		}
		switch (dev_state) {
		case QLA8XXX_DEV_READY:
			ha->flags.nic_core_reset_owner = 0;
			goto rel_lock;
		case QLA8XXX_DEV_COLD:
			rval = qla82xx_device_bootstrap(vha);
			break;
		case QLA8XXX_DEV_INITIALIZING:
			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);
			break;
		case QLA8XXX_DEV_NEED_RESET:
			if (!ql2xdontresethba)
				qla82xx_need_reset_handler(vha);
			else {
				qla82xx_idc_unlock(ha);
				msleep(1000);
				qla82xx_idc_lock(ha);
			}
			dev_init_timeout = jiffies +
			    (ha->fcoe_dev_init_timeout * HZ);
			break;
		case QLA8XXX_DEV_NEED_QUIESCENT:
			qla82xx_need_qsnt_handler(vha);
			/* Reset timeout value after quiescence handler */
			dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout\
							* HZ);
			break;
		case QLA8XXX_DEV_QUIESCENT:
			/* Owner will exit and other will wait for the state
			 * to get changed
			 */
			if (ha->flags.quiesce_owner)
				goto rel_lock;

			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);

			/* Reset timeout value after quiescence handler */
			dev_init_timeout = jiffies + (ha->fcoe_dev_init_timeout\
							* HZ);
			break;
		case QLA8XXX_DEV_FAILED:
			qla8xxx_dev_failed_handler(vha);
			rval = QLA_FUNCTION_FAILED;
			goto exit;
		default:
			qla82xx_idc_unlock(ha);
			msleep(1000);
			qla82xx_idc_lock(ha);
		}
		loopcount++;
	}
rel_lock:
	qla82xx_idc_unlock(ha);
exit:
	return rval;
}