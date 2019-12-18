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
struct mpc5200_wdt {scalar_t__ count; } ;
struct inode {int dummy; } ;
struct file {struct mpc5200_wdt* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_active ; 
 int /*<<< orphan*/  mpc5200_wdt_stop (struct mpc5200_wdt*) ; 

__attribute__((used)) static int mpc5200_wdt_release(struct inode *inode, struct file *file)
{
#if WATCHDOG_NOWAYOUT == 0
	struct mpc5200_wdt *wdt = file->private_data;
	mpc5200_wdt_stop(wdt);
	wdt->count = 0;		/* == disabled */
#endif
	clear_bit(0, &is_active);
	return 0;
}