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
struct hpet_dev {int dummy; } ;
struct file {struct hpet_dev* private_data; } ;

/* Variables and functions */
 int hpet_ioctl_common (struct hpet_dev*,unsigned int,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hpet_ioctl(struct inode *inode, struct file *file, unsigned int cmd,
	   unsigned long arg)
{
	struct hpet_dev *devp;

	devp = file->private_data;
	return hpet_ioctl_common(devp, cmd, arg, 0);
}