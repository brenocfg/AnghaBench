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
 int /*<<< orphan*/  mpc8xxx_wdt_pr_warn (char*) ; 
 int /*<<< orphan*/  mpc8xxx_wdt_timer_ping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  wdt_is_open ; 

__attribute__((used)) static int mpc8xxx_wdt_release(struct inode *inode, struct file *file)
{
	if (!nowayout)
		mpc8xxx_wdt_timer_ping(0);
	else
		mpc8xxx_wdt_pr_warn("watchdog closed");
	clear_bit(0, &wdt_is_open);
	return 0;
}