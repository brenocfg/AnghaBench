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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int SYS_CNTRL_M20 ; 
 int /*<<< orphan*/  SYS_COUNTER_CNTRL ; 
 int /*<<< orphan*/  SYS_TOYMATCH2 ; 
 int /*<<< orphan*/  SYS_TOYREAD ; 
 int /*<<< orphan*/  SYS_WAKEMSK ; 
 int /*<<< orphan*/  SYS_WAKESRC ; 
 int /*<<< orphan*/  alchemy_gpio1_input_enable () ; 
 int au_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_sleep () ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ db1x_pm_sleep_secs ; 
 scalar_t__ db1x_pm_wakemsk ; 

__attribute__((used)) static int db1x_pm_enter(suspend_state_t state)
{
	/* enable GPIO based wakeup */
	alchemy_gpio1_input_enable();

	/* clear and setup wake cause and source */
	au_writel(0, SYS_WAKEMSK);
	au_sync();
	au_writel(0, SYS_WAKESRC);
	au_sync();

	au_writel(db1x_pm_wakemsk, SYS_WAKEMSK);
	au_sync();

	/* setup 1Hz-timer-based wakeup: wait for reg access */
	while (au_readl(SYS_COUNTER_CNTRL) & SYS_CNTRL_M20)
		asm volatile ("nop");

	au_writel(au_readl(SYS_TOYREAD) + db1x_pm_sleep_secs, SYS_TOYMATCH2);
	au_sync();

	/* wait for value to really hit the register */
	while (au_readl(SYS_COUNTER_CNTRL) & SYS_CNTRL_M20)
		asm volatile ("nop");

	/* ...and now the sandman can come! */
	au_sleep();

	return 0;
}