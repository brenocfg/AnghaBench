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
typedef  int u32 ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cycle_kernel_lock () ; 
 int iminor (struct inode*) ; 
 int mask ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int cs5535_gpio_open(struct inode *inode, struct file *file)
{
	u32 m = iminor(inode);

	cycle_kernel_lock();
	/* the mask says which pins are usable by this driver */
	if ((mask & (1 << m)) == 0)
		return -EINVAL;

	return nonseekable_open(inode, file);
}