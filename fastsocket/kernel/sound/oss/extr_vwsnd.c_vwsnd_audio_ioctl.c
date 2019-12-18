#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  io_mutex; } ;
typedef  TYPE_1__ vwsnd_dev_t ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vwsnd_audio_do_ioctl (struct inode*,struct file*,unsigned int,unsigned long) ; 

__attribute__((used)) static int vwsnd_audio_ioctl(struct inode *inode,
				struct file *file,
				unsigned int cmd,
				unsigned long arg)
{
	vwsnd_dev_t *devc = (vwsnd_dev_t *) file->private_data;
	int ret;

	mutex_lock(&devc->io_mutex);
	ret = vwsnd_audio_do_ioctl(inode, file, cmd, arg);
	mutex_unlock(&devc->io_mutex);
	return ret;
}