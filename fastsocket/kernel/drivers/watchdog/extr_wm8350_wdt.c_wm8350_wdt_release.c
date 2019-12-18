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
struct wm8350 {int /*<<< orphan*/  dev; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct wm8350* get_wm8350 () ; 
 scalar_t__ wm8350_wdt_expect_close ; 
 int /*<<< orphan*/  wm8350_wdt_kick (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_wdt_stop (struct wm8350*) ; 
 int /*<<< orphan*/  wm8350_wdt_users ; 

__attribute__((used)) static int wm8350_wdt_release(struct inode *inode, struct file *file)
{
	struct wm8350 *wm8350 = get_wm8350();

	if (wm8350_wdt_expect_close)
		wm8350_wdt_stop(wm8350);
	else {
		dev_warn(wm8350->dev, "Watchdog device closed uncleanly\n");
		wm8350_wdt_kick(wm8350);
	}

	clear_bit(0, &wm8350_wdt_users);

	return 0;
}