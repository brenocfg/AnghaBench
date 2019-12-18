#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  busy; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__ flash ; 
 int /*<<< orphan*/  lock_kernel () ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
flash_open(struct inode *inode, struct file *file)
{
	lock_kernel();
	if (test_and_set_bit(0, (void *)&flash.busy) != 0) {
		unlock_kernel();
		return -EBUSY;
	}

	unlock_kernel();
	return 0;
}