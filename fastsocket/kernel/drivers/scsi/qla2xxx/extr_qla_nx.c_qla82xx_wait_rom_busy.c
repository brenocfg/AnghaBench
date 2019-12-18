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
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_GLB_STATUS ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 long qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 long rom_max_timeout ; 

__attribute__((used)) static int
qla82xx_wait_rom_busy(struct qla_hw_data *ha)
{
	long timeout = 0;
	long done = 0 ;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while (done == 0) {
		done = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_STATUS);
		done &= 4;
		timeout++;
		if (timeout >= rom_max_timeout) {
			ql_dbg(ql_dbg_p3p, vha, 0xb00a,
			    "%s: Timeout reached waiting for rom busy.\n",
			    QLA2XXX_DRIVER_NAME);
			return -1;
		}
	}
	return 0;
}