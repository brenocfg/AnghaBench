#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct saa7146_fh {scalar_t__ type; struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_3__* ext; TYPE_2__* ext_vv_data; } ;
struct file {struct saa7146_fh* private_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* release ) (struct saa7146_dev*,struct file*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* release ) (struct saa7146_dev*,struct file*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  module; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct file*) ;} ;
struct TYPE_7__ {int capabilities; TYPE_1__ vbi_fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int ERESTARTSYS ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int /*<<< orphan*/  kfree (struct saa7146_fh*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_devices_lock ; 
 TYPE_5__ saa7146_vbi_uops ; 
 TYPE_4__ saa7146_video_uops ; 
 int /*<<< orphan*/  stub1 (struct saa7146_dev*,struct file*) ; 
 int /*<<< orphan*/  stub2 (struct file*) ; 
 int /*<<< orphan*/  stub3 (struct saa7146_dev*,struct file*) ; 

__attribute__((used)) static int fops_release(struct file *file)
{
	struct saa7146_fh  *fh  = file->private_data;
	struct saa7146_dev *dev = fh->dev;

	DEB_EE(("file:%p\n", file));

	if (mutex_lock_interruptible(&saa7146_devices_lock))
		return -ERESTARTSYS;

	if( fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
		if (dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE)
			saa7146_vbi_uops.release(dev,file);
		if (dev->ext_vv_data->vbi_fops.release)
			dev->ext_vv_data->vbi_fops.release(file);
	} else {
		saa7146_video_uops.release(dev,file);
	}

	module_put(dev->ext->module);
	file->private_data = NULL;
	kfree(fh);

	mutex_unlock(&saa7146_devices_lock);

	return 0;
}