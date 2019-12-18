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
struct mpcore_wdt {int expect_close; int /*<<< orphan*/  timer_alive; int /*<<< orphan*/  dev; } ;
struct inode {int dummy; } ;
struct file {struct mpcore_wdt* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mpcore_wdt_keepalive (struct mpcore_wdt*) ; 
 int /*<<< orphan*/  mpcore_wdt_stop (struct mpcore_wdt*) ; 

__attribute__((used)) static int mpcore_wdt_release(struct inode *inode, struct file *file)
{
	struct mpcore_wdt *wdt = file->private_data;

	/*
	 *	Shut off the timer.
	 * 	Lock it in if it's a module and we set nowayout
	 */
	if (wdt->expect_close == 42)
		mpcore_wdt_stop(wdt);
	else {
		dev_printk(KERN_CRIT, wdt->dev,
				"unexpected close, not stopping watchdog!\n");
		mpcore_wdt_keepalive(wdt);
	}
	clear_bit(0, &wdt->timer_alive);
	wdt->expect_close = 0;
	return 0;
}