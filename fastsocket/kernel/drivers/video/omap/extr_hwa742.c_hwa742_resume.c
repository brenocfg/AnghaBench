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
struct TYPE_2__ {int /*<<< orphan*/  update_mode_before_suspend; int /*<<< orphan*/  sys_ck; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWA742_PLL_DIV_REG ; 
 int /*<<< orphan*/  HWA742_POWER_SAVE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 TYPE_1__ hwa742 ; 
 int hwa742_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_set_update_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwa742_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hwa742_resume(void)
{
	clk_enable(hwa742.sys_ck);

	/* Disable sleep mode */
	hwa742_write_reg(HWA742_POWER_SAVE, 0);
	while (1) {
		/* Loop until PLL output is stabilized */
		if (hwa742_read_reg(HWA742_PLL_DIV_REG) & (1 << 7))
			break;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(msecs_to_jiffies(5));
	}
	hwa742_set_update_mode(hwa742.update_mode_before_suspend);
}