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
struct file {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  opened ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int maint_open(struct inode *ino, struct file *filep)
{
	int ret;

	lock_kernel();
	/* only one open is allowed, so we test
	   it atomically */
	if (test_and_set_bit(0, &opened))
		ret = -EBUSY;
	else {
		filep->private_data = NULL;
		ret = nonseekable_open(ino, filep);
	}
	unlock_kernel();
	return ret;
}