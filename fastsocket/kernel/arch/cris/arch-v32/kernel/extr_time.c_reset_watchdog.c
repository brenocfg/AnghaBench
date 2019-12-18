#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  key; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cnt; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ reg_timer_rw_wd_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ETRAX_WD_CNT ; 
 int /*<<< orphan*/  ETRAX_WD_KEY_MASK ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 scalar_t__ WATCHDOG_MIN_FREE_PAGES ; 
 scalar_t__ nr_free_pages () ; 
 int /*<<< orphan*/  regi_timer0 ; 
 int /*<<< orphan*/  regk_timer_start ; 
 int /*<<< orphan*/  rw_wd_ctrl ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  watchdog_key ; 

void
reset_watchdog(void)
{
#if defined(CONFIG_ETRAX_WATCHDOG)
	reg_timer_rw_wd_ctrl wd_ctrl = { 0 };

	/* Only keep watchdog happy as long as we have memory left! */
	if(nr_free_pages() > WATCHDOG_MIN_FREE_PAGES) {
		/* Reset the watchdog with the inverse of the old key */
		/* Invert key, which is 7 bits */
		watchdog_key ^= ETRAX_WD_KEY_MASK;
		wd_ctrl.cnt = ETRAX_WD_CNT;
		wd_ctrl.cmd = regk_timer_start;
		wd_ctrl.key = watchdog_key;
		REG_WR(timer, regi_timer0, rw_wd_ctrl, wd_ctrl);
	}
#endif
}