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
 int /*<<< orphan*/  GEF_WDOG_FLAG_OPENED ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gef_wdt_handler_enable () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static int gef_wdt_open(struct inode *inode, struct file *file)
{
	if (test_and_set_bit(GEF_WDOG_FLAG_OPENED, &wdt_flags))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	gef_wdt_handler_enable();

	return nonseekable_open(inode, file);
}