#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device_shadow {int /*<<< orphan*/ * lock; } ;
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/  tvnorms; int /*<<< orphan*/  (* release ) (struct video_device*) ;int /*<<< orphan*/ * ioctl_ops; int /*<<< orphan*/ * fops; } ;
struct saa7146_dev {int /*<<< orphan*/  name; TYPE_2__* ext_vv_data; int /*<<< orphan*/  v4l2_lock; } ;
struct TYPE_4__ {int num_stds; TYPE_1__* stds; int /*<<< orphan*/  ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  INFO (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct video_device* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_node_name (struct video_device*) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 struct video_device_shadow* video_device_shadow_get (struct video_device*) ; 
 int /*<<< orphan*/  video_fops ; 
 int video_register_device (struct video_device*,int,int) ; 
 int /*<<< orphan*/  video_set_drvdata (struct video_device*,struct saa7146_dev*) ; 

int saa7146_register_device(struct video_device **vid, struct saa7146_dev* dev,
			    char *name, int type)
{
	struct video_device *vfd;
	struct video_device_shadow *shvfd;
	int err;
	int i;

	DEB_EE(("dev:%p, name:'%s', type:%d\n",dev,name,type));

	// released by vfd->release
	vfd = video_device_alloc();
	if (vfd == NULL)
		return -ENOMEM;

	shvfd = video_device_shadow_get(vfd);
	if (shvfd == NULL)
		return -ENOMEM;

	vfd->fops = &video_fops;
	vfd->ioctl_ops = &dev->ext_vv_data->ops;
	vfd->release = video_device_release;
	shvfd->lock = &dev->v4l2_lock;
	vfd->tvnorms = 0;
	for (i = 0; i < dev->ext_vv_data->num_stds; i++)
		vfd->tvnorms |= dev->ext_vv_data->stds[i].id;
	strlcpy(vfd->name, name, sizeof(vfd->name));
	video_set_drvdata(vfd, dev);

	err = video_register_device(vfd, type, -1);
	if (err < 0) {
		ERR(("cannot register v4l2 device. skipping.\n"));
		video_device_release(vfd);
		return err;
	}

	INFO(("%s: registered device %s [v4l2]\n",
		dev->name, video_device_node_name(vfd)));

	*vid = vfd;
	return 0;
}