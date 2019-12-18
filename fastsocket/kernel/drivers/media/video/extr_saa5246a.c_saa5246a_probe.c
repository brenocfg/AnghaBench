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
struct v4l2_subdev {int dummy; } ;
struct saa5246a_device {int* is_searching; int /*<<< orphan*/ * vdev; int /*<<< orphan*/ * pgbuf; int /*<<< orphan*/  lock; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAJOR_VERSION ; 
 int /*<<< orphan*/  MINOR_VERSION ; 
 int NUM_DAUS ; 
 int /*<<< orphan*/  VFL_TYPE_VTX ; 
 int /*<<< orphan*/  kfree (struct saa5246a_device*) ; 
 struct saa5246a_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa5246a_ops ; 
 int /*<<< orphan*/  saa_template ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release (int /*<<< orphan*/ *) ; 
 int video_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (int /*<<< orphan*/ *,struct saa5246a_device*) ; 

__attribute__((used)) static int saa5246a_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int pgbuf;
	int err;
	struct saa5246a_device *t;
	struct v4l2_subdev *sd;

	v4l_info(client, "chip found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);
	v4l_info(client, "VideoText version %d.%d\n",
			MAJOR_VERSION, MINOR_VERSION);
	t = kzalloc(sizeof(*t), GFP_KERNEL);
	if (t == NULL)
		return -ENOMEM;
	sd = &t->sd;
	v4l2_i2c_subdev_init(sd, client, &saa5246a_ops);
	mutex_init(&t->lock);

	/* Now create a video4linux device */
	t->vdev = video_device_alloc();
	if (t->vdev == NULL) {
		kfree(t);
		return -ENOMEM;
	}
	memcpy(t->vdev, &saa_template, sizeof(*t->vdev));

	for (pgbuf = 0; pgbuf < NUM_DAUS; pgbuf++) {
		memset(t->pgbuf[pgbuf], ' ', sizeof(t->pgbuf[0]));
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