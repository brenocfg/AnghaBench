#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct video_device_shadow {int /*<<< orphan*/ * lock; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct soc_camera_link {int (* add_device ) (struct soc_camera_link*,TYPE_3__*) ;int /*<<< orphan*/  regulators; int /*<<< orphan*/  num_regulators; int /*<<< orphan*/  (* del_device ) (struct soc_camera_link*) ;scalar_t__ board_info; scalar_t__ module_name; int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ) ;} ;
struct soc_camera_host {TYPE_2__* ops; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct soc_camera_device {int /*<<< orphan*/  vdev; int /*<<< orphan*/  video_lock; TYPE_3__ dev; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  user_height; int /*<<< orphan*/  user_width; int /*<<< orphan*/  pdev; } ;
struct device {TYPE_1__* driver; int /*<<< orphan*/  kobj; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int (* add ) (struct soc_camera_device*) ;int /*<<< orphan*/  (* remove ) (struct soc_camera_device*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_ANY ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  g_mbus_fmt ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_module (scalar_t__) ; 
 int /*<<< orphan*/  soc_camera_free_i2c (struct soc_camera_device*) ; 
 int /*<<< orphan*/  soc_camera_free_user_formats (struct soc_camera_device*) ; 
 int soc_camera_init_i2c (struct soc_camera_device*,struct soc_camera_link*) ; 
 int soc_camera_init_user_formats (struct soc_camera_device*) ; 
 int soc_camera_power_set (struct soc_camera_device*,struct soc_camera_link*,int) ; 
 struct v4l2_subdev* soc_camera_to_subdev (struct soc_camera_device*) ; 
 int soc_camera_video_start (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (struct soc_camera_device*) ; 
 int stub3 (struct soc_camera_link*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (struct soc_camera_link*) ; 
 int /*<<< orphan*/  stub5 (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stub6 (struct soc_camera_link*) ; 
 int /*<<< orphan*/  stub7 (struct soc_camera_device*) ; 
 scalar_t__ sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 struct device* to_soc_camera_control (struct soc_camera_device*) ; 
 struct soc_camera_device* to_soc_camera_dev (struct device*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  video ; 
 int video_dev_create (struct soc_camera_device*) ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ ) ; 
 struct video_device_shadow* video_device_shadow_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_probe(struct device *dev)
{
	struct soc_camera_device *icd = to_soc_camera_dev(dev);
	struct soc_camera_host *ici = to_soc_camera_host(dev->parent);
	struct soc_camera_link *icl = to_soc_camera_link(icd);
	struct device *control = NULL;
	struct v4l2_subdev *sd;
	struct v4l2_mbus_framefmt mf;
	struct video_device_shadow *shvdev;
	int ret;

	dev_info(dev, "Probing %s\n", dev_name(dev));

	ret = regulator_bulk_get(icd->pdev, icl->num_regulators,
				 icl->regulators);
	if (ret < 0)
		goto ereg;

	ret = soc_camera_power_set(icd, icl, 1);
	if (ret < 0)
		goto epower;

	/* The camera could have been already on, try to reset */
	if (icl->reset)
		icl->reset(icd->pdev);

	ret = ici->ops->add(icd);
	if (ret < 0)
		goto eadd;

	/* Must have icd->vdev before registering the device */
	ret = video_dev_create(icd);
	if (ret < 0)
		goto evdc;

	/* Non-i2c cameras, e.g., soc_camera_platform, have no board_info */
	if (icl->board_info) {
		ret = soc_camera_init_i2c(icd, icl);
		if (ret < 0)
			goto eadddev;
	} else if (!icl->add_device || !icl->del_device) {
		ret = -EINVAL;
		goto eadddev;
	} else {
		if (icl->module_name)
			ret = request_module(icl->module_name);

		ret = icl->add_device(icl, &icd->dev);
		if (ret < 0)
			goto eadddev;

		/*
		 * FIXME: this is racy, have to use driver-binding notification,
		 * when it is available
		 */
		control = to_soc_camera_control(icd);
		if (!control || !control->driver || !dev_get_drvdata(control) ||
		    !try_module_get(control->driver->owner)) {
			icl->del_device(icl);
			goto enodrv;
		}
	}

	/* At this point client .probe() should have run already */
	ret = soc_camera_init_user_formats(icd);
	if (ret < 0)
		goto eiufmt;

	icd->field = V4L2_FIELD_ANY;

	shvdev = video_device_shadow_get(icd->vdev);
	shvdev->lock = &icd->video_lock;

	/*
	 * ..._video_start() will create a device node, video_register_device()
	 * itself is protected against concurrent open() calls, but we also have
	 * to protect our data.
	 */
	mutex_lock(&icd->video_lock);

	ret = soc_camera_video_start(icd);
	if (ret < 0)
		goto evidstart;

	/* Try to improve our guess of a reasonable window format */
	sd = soc_camera_to_subdev(icd);
	if (!v4l2_subdev_call(sd, video, g_mbus_fmt, &mf)) {
		icd->user_width		= mf.width;
		icd->user_height	= mf.height;
		icd->colorspace		= mf.colorspace;
		icd->field		= mf.field;
	}

	/* Do we have to sysfs_remove_link() before device_unregister()? */
	if (sysfs_create_link(&icd->dev.kobj, &to_soc_camera_control(icd)->kobj,
			      "control"))
		dev_warn(&icd->dev, "Failed creating the control symlink\n");

	ici->ops->remove(icd);

	soc_camera_power_set(icd, icl, 0);

	mutex_unlock(&icd->video_lock);

	return 0;

evidstart:
	mutex_unlock(&icd->video_lock);
	soc_camera_free_user_formats(icd);
eiufmt:
	if (icl->board_info) {
		soc_camera_free_i2c(icd);
	} else {
		icl->del_device(icl);
		module_put(control->driver->owner);
	}
enodrv:
eadddev:
	video_device_release(icd->vdev);
evdc:
	ici->ops->remove(icd);
eadd:
	soc_camera_power_set(icd, icl, 0);
epower:
	regulator_bulk_free(icl->num_regulators, icl->regulators);
ereg:
	return ret;
}