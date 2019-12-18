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
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int vfd_is_open ; 

__attribute__((used)) static int briq_panel_open(struct inode *ino, struct file *filep)
{
	lock_kernel();
	/* enforce single access, vfd_is_open is protected by BKL */
	if (vfd_is_open) {
		unlock_kernel();
		return -EBUSY;
	}
	vfd_is_open = 1;

	unlock_kernel();
	return 0;
}