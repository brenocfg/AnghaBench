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
 int CRYPTOCOP_MINOR ; 
 int EINVAL ; 
 int /*<<< orphan*/  cycle_kernel_lock () ; 
 int iminor (struct inode*) ; 

__attribute__((used)) static int cryptocop_open(struct inode *inode, struct file *filp)
{
	int p = iminor(inode);

	cycle_kernel_lock();
	if (p != CRYPTOCOP_MINOR) return -EINVAL;

	filp->private_data = NULL;
	return 0;
}