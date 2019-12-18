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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct twl4030_wdt {int /*<<< orphan*/  state; TYPE_1__ miscdev; } ;
struct inode {int dummy; } ;
struct file {struct twl4030_wdt* private_data; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  TWL4030_WDT_STATE_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nowayout ; 
 scalar_t__ twl4030_wdt_disable (struct twl4030_wdt*) ; 
 int /*<<< orphan*/  twl4030_wdt_enable (struct twl4030_wdt*) ; 

__attribute__((used)) static int twl4030_wdt_release(struct inode *inode, struct file *file)
{
	struct twl4030_wdt *wdt = file->private_data;
	if (nowayout) {
		dev_alert(wdt->miscdev.parent,
		       "Unexpected close, watchdog still running!\n");
		twl4030_wdt_enable(wdt);
	} else {
		if (twl4030_wdt_disable(wdt))
			return -EFAULT;
		wdt->state &= ~TWL4030_WDT_STATE_ACTIVE;
	}

	clear_bit(0, &wdt->state);
	return 0;
}