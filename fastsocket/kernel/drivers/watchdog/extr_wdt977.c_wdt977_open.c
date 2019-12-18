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
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ nowayout ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_alive ; 
 int /*<<< orphan*/  wdt977_start () ; 

__attribute__((used)) static int wdt977_open(struct inode *inode, struct file *file)
{
	/* If the watchdog is alive we don't need to start it again */
	if (test_and_set_bit(0, &timer_alive))
		return -EBUSY;

	if (nowayout)
		__module_get(THIS_MODULE);

	wdt977_start();
	return nonseekable_open(inode, file);
}