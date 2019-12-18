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
struct v4l2_subdev {int dummy; } ;
struct saa5249_device {int addr; int* is_searching; int /*<<< orphan*/ * vdev; TYPE_2__* vdau; int /*<<< orphan*/  lock; struct v4l2_subdev sd; TYPE_1__* adapter; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int* is_searching; int /*<<< orphan*/ * vdev; TYPE_2__* vdau; int /*<<< orphan*/  lock; struct v4l2_subdev sd; TYPE_1__* adapter; } ;
struct TYPE_4__ {int clrfound; int stopped; scalar_t__ expire; int /*<<< orphan*/  laststat; int /*<<< orphan*/  sregs; int /*<<< orphan*/  pgbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NUM_DAUS ; 
 int /*<<< orphan*/  VFL_TYPE_VTX ; 
 int VTX_VER_MAJ ; 
 int /*<<< orphan*/  VTX_VER_MIN ; 
 int /*<<< orphan*/  kfree (struct saa5249_device*) ; 
 struct saa5249_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa5249_ops ; 
 int /*<<< orphan*/  saa_template ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct saa5249_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct saa5249_device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 int video_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (int /*<<< orphan*/ *,struct saa5249_device*) ; 

__attribute__((used)) static int saa5249_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int pgbuf;
	int err;
	struct saa5249_device *t;
	struct v4l2_subdev *sd;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
	v4l_info(client, "VideoText version %d.%d\n",
			VTX_VER_MAJ, VTX_VER_MIN);
	t = kzalloc(sizeof(*t), GFP_KERNEL);
	if (t == NULL)
		return -ENOMEM;
	sd = &t->sd;
	v4l2_i2c_subdev_init(sd, client, &saa5249_ops);
	mutex_init(&t->lock);

	/* Now create a video4linux device */
	t->vdev = video_device_alloc();
	if (t->vdev == NULL) {
		kfree(t);
		kfree(client);
		return -ENOMEM;
	}
	memcpy(t->vdev, &saa_template, sizeof(*t->vdev));

	for (pgbuf = 0; pgbuf < NUM_DAUS; pgbuf++) {
		memset(t->vdau[pgbuf].pgbuf, ' ', sizeof(t->vdau[0].pgbuf));
		memset(t->vdau[pgbuf].sregs, 0, sizeof(t->vdau[0].sregs));
		memset(t->vdau[pgbuf].laststat, 0, sizeof(t->vdau[0].laststat));
		t->vdau[pgbuf].expire = 0;
		t->vdau[pgbuf].clrfound = true;
		t->vdau[pgbuf].stopped = true;
		t->is_searching[pgbuf] = false;
	}
	video_set_drvdata(t->vdev, t);

	/* Register it */
	err = video_register_device(t->vdev, VFL_TYPE_VTX, -1);
	if (err < 0) {
		video_device_release(t->vdev);
		kfree(t);
		return err;
	}
	return 0;
}