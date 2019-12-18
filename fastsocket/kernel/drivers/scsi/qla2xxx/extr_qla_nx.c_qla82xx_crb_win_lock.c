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
struct qla_hw_data {int /*<<< orphan*/  portnum; } ;

/* Variables and functions */
 int CRB_WIN_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  PCIE_SEM7_LOCK ; 
 int /*<<< orphan*/  QLA82XX_CRB_WIN_LOCK_ID ; 
 int /*<<< orphan*/  QLA82XX_PCIE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  in_atomic () ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int
qla82xx_crb_win_lock(struct qla_hw_data *ha)
{
	int i;
	int done = 0, timeout = 0;

	while (!done) {
		/* acquire semaphore3 from PCI HW block */
		done = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM7_LOCK));
		if (done == 1)
			break;
		if (timeout >= CRB_WIN_LOCK_TIMEOUT)
			return -1;
		timeout++;

		/* Yield CPU */
		if (!in_atomic())
			schedule();
		else {
			for (i = 0; i < 20; i++)
				cpu_relax();
		}
	}
	qla82xx_wr_32(ha, QLA82XX_CRB_WIN_LOCK_ID, ha->portnum);
	return 0;
}