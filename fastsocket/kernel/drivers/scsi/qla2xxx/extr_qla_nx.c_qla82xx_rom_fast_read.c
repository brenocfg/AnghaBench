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
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int qla82xx_do_rom_fast_read (struct qla_hw_data*,int,int*) ; 
 scalar_t__ qla82xx_rom_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_rom_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla82xx_rom_fast_read(struct qla_hw_data *ha, int addr, int *valp)
{
	int ret, loops = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while ((qla82xx_rom_lock(ha) != 0) && (loops < 50000)) {
		udelay(100);
		schedule();
		loops++;
	}
	if (loops >= 50000) {
		ql_log(ql_log_fatal, vha, 0x00b9,
		    "Failed to acquire SEM2 lock.\n");
		return -1;
	}
	ret = qla82xx_do_rom_fast_read(ha, addr, valp);
	qla82xx_rom_unlock(ha);
	return ret;
}