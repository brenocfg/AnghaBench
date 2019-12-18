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
struct mpcore_wdt {int /*<<< orphan*/  timer_alive; } ;
struct inode {int dummy; } ;
struct file {struct mpcore_wdt* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpcore_wdt_dev ; 
 int /*<<< orphan*/  mpcore_wdt_start (struct mpcore_wdt*) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 struct mpcore_wdt* platform_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpcore_wdt_open(struct inode *inode, struct file *file)
{
	struct mpcore_wdt *wdt = platform_get_drvdata(mpcore_wdt_dev);

	if (test_and_set_bit(0, &wdt->timer_alive))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	file->private_data = wdt;

	/*
	 *	Activate timer
	 */
	mpcore_wdt_start(wdt);

	return nonseekable_open(inode, file);
}