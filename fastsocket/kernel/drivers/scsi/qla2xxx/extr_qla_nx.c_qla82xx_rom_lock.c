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
typedef  void* uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_SEM2_LOCK ; 
 int /*<<< orphan*/  QLA82XX_PCIE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLA82XX_ROM_LOCK_ID ; 
 int /*<<< orphan*/  ROM_LOCK_DRIVER ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,void*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 void* qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int qla82xx_rom_lock_timeout ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_rom_lock(struct qla_hw_data *ha)
{
	int done = 0, timeout = 0;
	uint32_t lock_owner = 0;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	while (!done) {
		/* acquire semaphore2 from PCI HW block */
		done = qla82xx_rd_32(ha, QLA82XX_PCIE_REG(PCIE_SEM2_LOCK));
		if (done == 1)
			break;
		if (timeout >= qla82xx_rom_lock_timeout) {
			lock_owner = qla82xx_rd_32(ha, QLA82XX_ROM_LOCK_ID);
			ql_dbg(ql_dbg_p3p, vha, 0xb085,
			    "Failed to acquire rom lock, acquired by %d.\n",
			    lock_owner);
			return -1;
		}
		timeout++;
	}
	qla82xx_wr_32(ha, QLA82XX_ROM_LOCK_ID, ROM_LOCK_DRIVER);
	return 0;
}