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
struct file {int f_flags; } ;

/* Variables and functions */
 int O_EXCL ; 
 int cpustate_get_ref (int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int cpustate_open(struct inode *inode, struct file *file)
{
	int ret;

	lock_kernel();
	ret = cpustate_get_ref((file->f_flags & O_EXCL));
	unlock_kernel();

	return ret;
}