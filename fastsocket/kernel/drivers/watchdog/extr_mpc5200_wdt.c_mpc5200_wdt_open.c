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
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  is_active ; 
 int /*<<< orphan*/  mpc5200_wdt_set_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc5200_wdt_start (int /*<<< orphan*/ ) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_global ; 

__attribute__((used)) static int mpc5200_wdt_open(struct inode *inode, struct file *file)
{
	/* /dev/watchdog can only be opened once */
	if (test_and_set_bit(0, &is_active))
		return -EBUSY;

	/* Set and activate the watchdog */
	mpc5200_wdt_set_timeout(wdt_global, 30);
	mpc5200_wdt_start(wdt_global);
	file->private_data = wdt_global;
	return nonseekable_open(inode, file);
}