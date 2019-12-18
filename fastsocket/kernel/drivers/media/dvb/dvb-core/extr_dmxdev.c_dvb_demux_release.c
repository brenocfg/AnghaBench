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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/ * f_op; struct dmxdev_filter* private_data; } ;
struct dmxdev_filter {struct dmxdev* dev; } ;
struct dmxdev {int exit; int /*<<< orphan*/  mutex; TYPE_1__* dvbdev; } ;
struct TYPE_2__ {int users; int /*<<< orphan*/  wait_queue; } ;

/* Variables and functions */
 int dvb_dmxdev_filter_free (struct dmxdev*,struct dmxdev_filter*) ; 
 int /*<<< orphan*/  fops_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_demux_release(struct inode *inode, struct file *file)
{
	struct dmxdev_filter *dmxdevfilter = file->private_data;
	struct dmxdev *dmxdev = dmxdevfilter->dev;

	int ret;

	ret = dvb_dmxdev_filter_free(dmxdev, dmxdevfilter);

	mutex_lock(&dmxdev->mutex);
	dmxdev->dvbdev->users--;
	if(dmxdev->dvbdev->users==1 && dmxdev->exit==1) {
		fops_put(file->f_op);
		file->f_op = NULL;
		mutex_unlock(&dmxdev->mutex);
		wake_up(&dmxdev->dvbdev->wait_queue);
	} else
		mutex_unlock(&dmxdev->mutex);

	return ret;
}