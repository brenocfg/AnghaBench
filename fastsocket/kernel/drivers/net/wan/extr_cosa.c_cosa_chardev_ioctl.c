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
struct file {struct channel_data* private_data; } ;
struct cosa_data {int dummy; } ;
struct channel_data {struct cosa_data* cosa; } ;

/* Variables and functions */
 int cosa_ioctl_common (struct cosa_data*,struct channel_data*,unsigned int,unsigned long) ; 

__attribute__((used)) static int cosa_chardev_ioctl(struct inode *inode, struct file *file,
	unsigned int cmd, unsigned long arg)
{
	struct channel_data *channel = file->private_data;
	struct cosa_data *cosa = channel->cosa;
	return cosa_ioctl_common(cosa, channel, cmd, arg);
}