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

/* Variables and functions */
 int /*<<< orphan*/  GPIO ; 
 int /*<<< orphan*/  WDTCFG ; 
 int /*<<< orphan*/  WDTCTRL ; 
 int /*<<< orphan*/  WDTS_USE_GP ; 
 int /*<<< orphan*/  WDTVALLSB ; 
 int /*<<< orphan*/  WDTVALMSB ; 
 int WDT_CIRINT ; 
 int WDT_GAMEPORT ; 
 int WDT_KRST ; 
 int WDT_PWROK ; 
 int WDT_TOV1 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 
 int /*<<< orphan*/  superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int /*<<< orphan*/  superio_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testmode ; 
 int timeout ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static void wdt_start(void)
{
	unsigned long flags;

	spin_lock_irqsave(&spinlock, flags);
	superio_enter();

	superio_select(GPIO);
	if (test_bit(WDTS_USE_GP, &wdt_status))
		superio_outb(WDT_GAMEPORT, WDTCTRL);
	else
		superio_outb(WDT_CIRINT, WDTCTRL);
	if (!testmode)
		superio_outb(WDT_TOV1 | WDT_KRST | WDT_PWROK, WDTCFG);
	else
		superio_outb(WDT_TOV1, WDTCFG);
	superio_outb(timeout>>8, WDTVALMSB);
	superio_outb(timeout, WDTVALLSB);

	superio_exit();
	spin_unlock_irqrestore(&spinlock, flags);
}