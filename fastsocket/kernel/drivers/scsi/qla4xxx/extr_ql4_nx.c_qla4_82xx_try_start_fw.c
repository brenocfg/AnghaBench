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
struct TYPE_2__ {int /*<<< orphan*/  flt_region_fw; } ;
struct scsi_qla_host {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int qla4_82xx_start_firmware (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int qla4_8xxx_get_flash_info (struct scsi_qla_host*) ; 

int qla4_82xx_try_start_fw(struct scsi_qla_host *ha)
{
	int rval = QLA_ERROR;

	/*
	 * FW Load priority:
	 * 1) Operational firmware residing in flash.
	 * 2) Fail
	 */

	ql4_printk(KERN_INFO, ha,
	    "FW: Retrieving flash offsets from FLT/FDT ...\n");
	rval = qla4_8xxx_get_flash_info(ha);
	if (rval != QLA_SUCCESS)
		return rval;

	ql4_printk(KERN_INFO, ha,
	    "FW: Attempting to load firmware from flash...\n");
	rval = qla4_82xx_start_firmware(ha, ha->hw.flt_region_fw);

	if (rval != QLA_SUCCESS) {
		ql4_printk(KERN_ERR, ha, "FW: Load firmware from flash"
		    " FAILED...\n");
		return rval;
	}

	return rval;
}