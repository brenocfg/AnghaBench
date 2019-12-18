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
struct video_device {scalar_t__ vfl_type; } ;
struct saa7146_fh {int type; struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_3__* ext; TYPE_2__* ext_vv_data; } ;
struct file {struct saa7146_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_10__ {int (* open ) (struct saa7146_dev*,struct file*) ;} ;
struct TYPE_9__ {int (* open ) (struct saa7146_dev*,struct file*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  module; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* open ) (struct file*) ;} ;
struct TYPE_7__ {int capabilities; TYPE_1__ vbi_fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int /*<<< orphan*/  DEB_S (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ V4L2_BUF_TYPE_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  kfree (struct saa7146_fh*) ; 
 struct saa7146_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa7146_devices_lock ; 
 TYPE_5__ saa7146_vbi_uops ; 
 TYPE_4__ saa7146_video_uops ; 
 int stub1 (struct saa7146_dev*,struct file*) ; 
 int /*<<< orphan*/  stub2 (struct file*) ; 
 int stub3 (struct saa7146_dev*,struct file*) ; 
 scalar_t__ try_module_get (int /*<<< orphan*/ ) ; 
 struct video_device* video_devdata (struct file*) ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 struct saa7146_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int fops_open(struct file *file)
{
	struct video_device *vdev = video_devdata(file);
	struct saa7146_dev *dev = video_drvdata(file);
	struct saa7146_fh *fh = NULL;
	int result = 0;

	enum v4l2_buf_type type;

	DEB_EE(("file:%p, dev:%s\n", file, video_device_node_name(vdev)));

	if (mutex_lock_interruptible(&saa7146_devices_lock))
		return -ERESTARTSYS;

	DEB_D(("using: %p\n",dev));

	type = vdev->vfl_type == VFL_TYPE_GRABBER
	     ? V4L2_BUF_TYPE_VIDEO_CAPTURE
	     : V4L2_BUF_TYPE_VBI_CAPTURE;

	/* check if an extension is registered */
	if( NULL == dev->ext ) {
		DEB_S(("no extension registered for this device.\n"));
		result = -ENODEV;
		goto out;
	}

	/* allocate per open data */
	fh = kzalloc(sizeof(*fh),GFP_KERNEL);
	if (NULL == fh) {
		DEB_S(("cannot allocate memory for per open data.\n"));
		result = -ENOMEM;
		goto out;
	}

	file->private_data = fh;
	fh->dev = dev;
	fh->type = type;

	if( fh->type == V4L2_BUF_TYPE_VBI_CAPTURE) {
		DEB_S(("initializing vbi...\n"));
		if (dev->ext_vv_data->capabilities & V4L2_CAP_VBI_CAPTURE)
			result = saa7146_vbi_uops.open(dev,file);
		if (dev->ext_vv_data->vbi_fops.open)
			dev->ext_vv_data->vbi_fops.open(file);
	} else {
		DEB_S(("initializing video...\n"));
		result = saa7146_video_uops.open(dev,file);
	}

	if (0 != result) {
		goto out;
	}

	if( 0 == try_module_get(dev->ext->module)) {
		result = -EINVAL;
		goto out;
	}

	result = 0;
out:
	if (fh && result != 0) {
		kfree(fh);
		file->private_data = NULL;
	}
	mutex_unlock(&saa7146_devices_lock);
	return result;
}