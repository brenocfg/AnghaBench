#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  users; TYPE_1__ miscdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  at32_wdt_pat () ; 
 int /*<<< orphan*/  at32_wdt_stop () ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int expect_release ; 
 TYPE_2__* wdt ; 

__attribute__((used)) static int at32_wdt_close(struct inode *inode, struct file *file)
{
	if (expect_release == 42) {
		at32_wdt_stop();
	} else {
		dev_dbg(wdt->miscdev.parent,
			"unexpected close, not stopping watchdog!\n");
		at32_wdt_pat();
	}
	clear_bit(1, &wdt->users);
	expect_release = 0;
	return 0;
}