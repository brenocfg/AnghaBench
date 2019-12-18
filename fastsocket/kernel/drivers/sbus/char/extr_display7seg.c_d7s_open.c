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
 scalar_t__ D7S_MINOR ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cycle_kernel_lock () ; 
 int /*<<< orphan*/  d7s_users ; 
 scalar_t__ iminor (struct inode*) ; 

__attribute__((used)) static int d7s_open(struct inode *inode, struct file *f)
{
	if (D7S_MINOR != iminor(inode))
		return -ENODEV;
	cycle_kernel_lock();
	atomic_inc(&d7s_users);
	return 0;
}