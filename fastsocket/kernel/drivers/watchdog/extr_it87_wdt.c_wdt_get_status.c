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
 int WDIOF_CARDRESET ; 
 int WDIOF_KEEPALIVEPING ; 
 int WDIOF_MAGICCLOSE ; 
 int /*<<< orphan*/  WDTCTRL ; 
 int /*<<< orphan*/  WDTS_EXPECTED ; 
 int /*<<< orphan*/  WDTS_KEEPALIVE ; 
 int /*<<< orphan*/  WDTS_TIMER_RUN ; 
 int WDT_ZERO ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 
 int /*<<< orphan*/  superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int superio_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ testmode ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int wdt_get_status(int *status)
{
	unsigned long flags;

	*status = 0;
	if (testmode) {
		spin_lock_irqsave(&spinlock, flags);
		superio_enter();
		superio_select(GPIO);
		if (superio_inb(WDTCTRL) & WDT_ZERO) {
			superio_outb(0x00, WDTCTRL);
			clear_bit(WDTS_TIMER_RUN, &wdt_status);
			*status |= WDIOF_CARDRESET;
		}

		superio_exit();
		spin_unlock_irqrestore(&spinlock, flags);
	}
	if (test_and_clear_bit(WDTS_KEEPALIVE, &wdt_status))
		*status |= WDIOF_KEEPALIVEPING;
	if (test_bit(WDTS_EXPECTED, &wdt_status))
		*status |= WDIOF_MAGICCLOSE;
	return 0;
}