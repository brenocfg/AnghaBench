#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  en; } ;
typedef  TYPE_1__ reg_iop_mpu_rw_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  MPU_BA_I (unsigned int) ; 
 TYPE_1__ MPU_DI () ; 
 TYPE_1__ MPU_HALT () ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  REG_WR_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_mpu ; 
 int /*<<< orphan*/  regi_iop_mpu ; 
 int /*<<< orphan*/  regk_iop_mpu_yes ; 
 int /*<<< orphan*/  rw_ctrl ; 
 int /*<<< orphan*/  rw_instr ; 
 int wait_mpu_idle () ; 

int iop_start_mpu(unsigned int start_addr)
{
	reg_iop_mpu_rw_ctrl mpu_ctrl = { .en = regk_iop_mpu_yes };
	int retval;

	/* disable MPU */
	if ((retval = wait_mpu_idle()) != 0)
		goto out;
	REG_WR(iop_mpu, regi_iop_mpu, rw_instr, MPU_HALT());
	if ((retval = wait_mpu_idle()) != 0)
		goto out;
	/* set PC and wait for it to bite */
	if ((retval = wait_mpu_idle()) != 0)
		goto out;
	REG_WR_INT(iop_mpu, regi_iop_mpu, rw_instr, MPU_BA_I(start_addr));
	if ((retval = wait_mpu_idle()) != 0)
		goto out;
	/* make sure the MPU starts executing with interrupts disabled */
	REG_WR(iop_mpu, regi_iop_mpu, rw_instr, MPU_DI());
	if ((retval = wait_mpu_idle()) != 0)
		goto out;
	/* enable MPU */
	REG_WR(iop_mpu, regi_iop_mpu, rw_ctrl, mpu_ctrl);
 out:
	return retval;
}