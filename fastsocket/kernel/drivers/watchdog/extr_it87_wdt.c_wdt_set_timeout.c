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
 int EINVAL ; 
 int /*<<< orphan*/  GPIO ; 
 int /*<<< orphan*/  WDTS_TIMER_RUN ; 
 int /*<<< orphan*/  WDTVALLSB ; 
 int /*<<< orphan*/  WDTVALMSB ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spinlock ; 
 int /*<<< orphan*/  superio_enter () ; 
 int /*<<< orphan*/  superio_exit () ; 
 int /*<<< orphan*/  superio_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int timeout ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int wdt_set_timeout(int t)
{
	unsigned long flags;

	if (t < 1 || t > 65535)
		return -EINVAL;

	timeout = t;

	spin_lock_irqsave(&spinlock, flags);
	if (test_bit(WDTS_TIMER_RUN, &wdt_status)) {
		superio_enter();

		superio_select(GPIO);
		superio_outb(t>>8, WDTVALMSB);
		superio_outb(t, WDTVALLSB);

		superio_exit();
	}
	spin_unlock_irqrestore(&spinlock, flags);
	return 0;
}