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

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int generic_permission (struct inode*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ proc_pid (struct inode*) ; 
 scalar_t__ task_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_fd_permission(struct inode *inode, int mask)
{
	int rv;

	rv = generic_permission(inode, mask, NULL);
	if (rv == 0)
		return 0;
	if (task_pid(current) == proc_pid(inode))
		rv = 0;
	return rv;
}