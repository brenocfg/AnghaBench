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
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_MOD ; 
 int /*<<< orphan*/  MPU_MOD ; 
 unsigned long long NSEC_PER_USEC ; 
 int /*<<< orphan*/  OMAP24XX_PM_WKST2 ; 
 int OMAP_LOGICRETSTATE ; 
 int OMAP_POWERSTATE_SHIFT ; 
 int /*<<< orphan*/  PM_PWSTCTRL ; 
 int /*<<< orphan*/  PM_WKST ; 
 int /*<<< orphan*/  PM_WKST1 ; 
 int /*<<< orphan*/  WKUP_MOD ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 scalar_t__ omap2_allow_mpu_retention () ; 
 scalar_t__ omap2_i2c_active () ; 
 scalar_t__ omap2_pm_debug ; 
 int /*<<< orphan*/  omap2_pm_dump (int,int,unsigned long long) ; 
 int /*<<< orphan*/  omap2_sram_idle () ; 
 int /*<<< orphan*/  prm_write_mod_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct timespec timespec_sub (struct timespec,struct timespec) ; 
 unsigned long long timespec_to_ns (struct timespec*) ; 

__attribute__((used)) static void omap2_enter_mpu_retention(void)
{
	int only_idle = 0;
	struct timespec ts_preidle, ts_postidle, ts_idle;

	/* Putting MPU into the WFI state while a transfer is active
	 * seems to cause the I2C block to timeout. Why? Good question. */
	if (omap2_i2c_active())
		return;

	/* The peripherals seem not to be able to wake up the MPU when
	 * it is in retention mode. */
	if (omap2_allow_mpu_retention()) {
		/* REVISIT: These write to reserved bits? */
		prm_write_mod_reg(0xffffffff, CORE_MOD, PM_WKST1);
		prm_write_mod_reg(0xffffffff, CORE_MOD, OMAP24XX_PM_WKST2);
		prm_write_mod_reg(0xffffffff, WKUP_MOD, PM_WKST);

		/* Try to enter MPU retention */
		prm_write_mod_reg((0x01 << OMAP_POWERSTATE_SHIFT) |
				  OMAP_LOGICRETSTATE,
				  MPU_MOD, PM_PWSTCTRL);
	} else {
		/* Block MPU retention */

		prm_write_mod_reg(OMAP_LOGICRETSTATE, MPU_MOD, PM_PWSTCTRL);
		only_idle = 1;
	}

	if (omap2_pm_debug) {
		omap2_pm_dump(only_idle ? 2 : 1, 0, 0);
		getnstimeofday(&ts_preidle);
	}

	omap2_sram_idle();

	if (omap2_pm_debug) {
		unsigned long long tmp;

		getnstimeofday(&ts_postidle);
		ts_idle = timespec_sub(ts_postidle, ts_preidle);
		tmp = timespec_to_ns(&ts_idle) * NSEC_PER_USEC;
		omap2_pm_dump(only_idle ? 2 : 1, 1, tmp);
	}
}