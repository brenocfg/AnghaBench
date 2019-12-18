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
 int EBUSY ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WDTS_DEV_OPEN ; 
 int /*<<< orphan*/  WDTS_LOCKED ; 
 int /*<<< orphan*/  WDTS_TIMER_RUN ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ exclusive ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_start () ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int wdt_open(struct inode *inode, struct file *file)
{
	if (exclusive && test_and_set_bit(WDTS_DEV_OPEN, &wdt_status))
		return -EBUSY;
	if (!test_and_set_bit(WDTS_TIMER_RUN, &wdt_status)) {
		if (nowayout && !test_and_set_bit(WDTS_LOCKED, &wdt_status))
			__module_get(THIS_MODULE);
		wdt_start();
	}
	return nonseekable_open(inode, file);
}