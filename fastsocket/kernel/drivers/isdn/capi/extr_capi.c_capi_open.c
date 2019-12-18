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
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * capidev_alloc () ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int
capi_open(struct inode *inode, struct file *file)
{
	int ret;
	
	lock_kernel();
	if (file->private_data)
		ret = -EEXIST;
	else if ((file->private_data = capidev_alloc()) == NULL)
		ret = -ENOMEM;
	else
		ret = nonseekable_open(inode, file);
	unlock_kernel();
	return ret;
}