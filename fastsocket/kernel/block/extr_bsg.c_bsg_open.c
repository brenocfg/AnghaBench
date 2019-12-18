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
struct file {struct bsg_device* private_data; } ;
struct bsg_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bsg_device*) ; 
 int PTR_ERR (struct bsg_device*) ; 
 struct bsg_device* bsg_get_device (struct inode*,struct file*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int bsg_open(struct inode *inode, struct file *file)
{
	struct bsg_device *bd;

	lock_kernel();
	bd = bsg_get_device(inode, file);
	unlock_kernel();

	if (IS_ERR(bd))
		return PTR_ERR(bd);

	file->private_data = bd;
	return 0;
}