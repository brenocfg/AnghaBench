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
 int BLOCK_PROTECT_BITS ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int ql82xx_rom_lock_d (struct qla_hw_data*) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla82xx_read_status_reg (struct qla_hw_data*,int*) ; 
 int /*<<< orphan*/  qla82xx_rom_unlock (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_write_disable_flash (struct qla_hw_data*) ; 
 int qla82xx_write_status_reg (struct qla_hw_data*,int) ; 

__attribute__((used)) static int
qla82xx_protect_flash(struct qla_hw_data *ha)
{
	int ret;
	uint32_t val;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	ret = ql82xx_rom_lock_d(ha);
	if (ret < 0) {
		ql_log(ql_log_warn, vha, 0xb016,
		    "ROM Lock failed.\n");
		return ret;
	}

	ret = qla82xx_read_status_reg(ha, &val);
	if (ret < 0)
		goto done_protect;

	val |= (BLOCK_PROTECT_BITS << 2);
	/* LOCK all sectors */
	ret = qla82xx_write_status_reg(ha, val);
	if (ret < 0)
		ql_log(ql_log_warn, vha, 0xb017,
		    "Write status register failed.\n");

	if (qla82xx_write_disable_flash(ha) != 0)
		ql_log(ql_log_warn, vha, 0xb018,
		    "Write disable failed.\n");
done_protect:
	qla82xx_rom_unlock(ha);
	return ret;
}