#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* wm831x ; 
 scalar_t__ wm831x_wdt_expect_close ; 
 int /*<<< orphan*/  wm831x_wdt_kick (TYPE_1__*) ; 
 int /*<<< orphan*/  wm831x_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  wm831x_wdt_users ; 

__attribute__((used)) static int wm831x_wdt_release(struct inode *inode, struct file *file)
{
	if (wm831x_wdt_expect_close)
		wm831x_wdt_stop(wm831x);
	else {
		dev_warn(wm831x->dev, "Watchdog device closed uncleanly\n");
		wm831x_wdt_kick(wm831x);
	}

	clear_bit(0, &wm831x_wdt_users);

	return 0;
}