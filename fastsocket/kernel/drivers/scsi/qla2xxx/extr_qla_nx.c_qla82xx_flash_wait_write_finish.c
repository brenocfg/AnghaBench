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
typedef  int uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_ABYTE_CNT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla82xx_read_status_reg (struct qla_hw_data*,int*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla82xx_flash_wait_write_finish(struct qla_hw_data *ha)
{
	long timeout = 0;
	uint32_t done = 1 ;
	uint32_t val;
	int ret = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);
	while ((done != 0) && (ret == 0)) {
		ret = qla82xx_read_status_reg(ha, &val);
		done = val & 1;
		timeout++;
		udelay(10);
		cond_resched();
		if (timeout >= 50000) {
			ql_log(ql_log_warn, vha, 0xb00d,
			    "Timeout reached waiting for write finish.\n");
			return -1;
		}
	}
	return ret;
}