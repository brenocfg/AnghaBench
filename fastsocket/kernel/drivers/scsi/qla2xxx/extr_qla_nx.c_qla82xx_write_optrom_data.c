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
typedef  int uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int qla82xx_write_flash_data (struct scsi_qla_host*,int*,int,int) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 

int
qla82xx_write_optrom_data(struct scsi_qla_host *vha, uint8_t *buf,
	uint32_t offset, uint32_t length)
{
	int rval;

	/* Suspend HBA. */
	scsi_block_requests(vha->host);
	rval = qla82xx_write_flash_data(vha, (uint32_t *)buf, offset,
		length >> 2);
	scsi_unblock_requests(vha->host);

	/* Convert return ISP82xx to generic */
	if (rval)
		rval = QLA_FUNCTION_FAILED;
	else
		rval = QLA_SUCCESS;
	return rval;
}