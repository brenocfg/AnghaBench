#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {void* nx_reset_timeout; void* nx_dev_init_timeout; scalar_t__ request_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  QLA82XX_IDC_PARAM_ADDR ; 
 void* ROM_DEV_INIT_TIMEOUT ; 
 void* ROM_DRV_RESET_ACK_TIMEOUT ; 
 scalar_t__ __constant_cpu_to_le32 (int) ; 
 int /*<<< orphan*/  is_qla8022 (struct scsi_qla_host*) ; 
 void* le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,void*) ; 
 int /*<<< orphan*/  qla4_82xx_read_optrom_data (struct scsi_qla_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qla4_82xx_get_idc_param(struct scsi_qla_host *ha)
{
#define QLA82XX_IDC_PARAM_ADDR      0x003e885c
	uint32_t *wptr;

	if (!is_qla8022(ha))
		return;
	wptr = (uint32_t *)ha->request_ring;
	qla4_82xx_read_optrom_data(ha, (uint8_t *)ha->request_ring,
			QLA82XX_IDC_PARAM_ADDR , 8);

	if (*wptr == __constant_cpu_to_le32(0xffffffff)) {
		ha->nx_dev_init_timeout = ROM_DEV_INIT_TIMEOUT;
		ha->nx_reset_timeout = ROM_DRV_RESET_ACK_TIMEOUT;
	} else {
		ha->nx_dev_init_timeout = le32_to_cpu(*wptr++);
		ha->nx_reset_timeout = le32_to_cpu(*wptr);
	}

	DEBUG2(ql4_printk(KERN_DEBUG, ha,
		"ha->nx_dev_init_timeout = %d\n", ha->nx_dev_init_timeout));
	DEBUG2(ql4_printk(KERN_DEBUG, ha,
		"ha->nx_reset_timeout = %d\n", ha->nx_reset_timeout));
	return;
}