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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int expect_close ; 
 int /*<<< orphan*/  open_lock ; 
 int /*<<< orphan*/  s3c2410wdt_keepalive () ; 
 int /*<<< orphan*/  s3c2410wdt_stop () ; 
 int /*<<< orphan*/  wdt_dev ; 

__attribute__((used)) static int s3c2410wdt_release(struct inode *inode, struct file *file)
{
	/*
	 *	Shut off the timer.
	 * 	Lock it in if it's a module and we set nowayout
	 */

	if (expect_close == 42)
		s3c2410wdt_stop();
	else {
		dev_err(wdt_dev, "Unexpected close, not stopping watchdog\n");
		s3c2410wdt_keepalive();
	}
	expect_close = 0;
	clear_bit(0, &open_lock);
	return 0;
}