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
struct si4713_device {int /*<<< orphan*/  sd; int /*<<< orphan*/  work; int /*<<< orphan*/  mutex; int /*<<< orphan*/  platform_data; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  platform_data; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  name; TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_DISABLED ; 
 int IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct si4713_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct si4713_device*) ; 
 struct si4713_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct si4713_device*) ; 
 int /*<<< orphan*/  si4713_handler ; 
 int si4713_initialize (struct si4713_device*) ; 
 int /*<<< orphan*/  si4713_subdev_ops ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int si4713_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	struct si4713_device *sdev;
	int rval;

	sdev = kzalloc(sizeof *sdev, GFP_KERNEL);
	if (!sdev) {
		dev_err(&client->dev, "Failed to alloc video device.\n");
		rval = -ENOMEM;
		goto exit;
	}

	sdev->platform_data = client->dev.platform_data;
	if (!sdev->platform_data) {
		v4l2_err(&sdev->sd, "No platform data registered.\n");
		rval = -ENODEV;
		goto free_sdev;
	}

	v4l2_i2c_subdev_init(&sdev->sd, client, &si4713_subdev_ops);

	mutex_init(&sdev->mutex);
	init_completion(&sdev->work);

	if (client->irq) {
		rval = request_irq(client->irq,
			si4713_handler, IRQF_TRIGGER_FALLING | IRQF_DISABLED,
			client->name, sdev);
		if (rval < 0) {
			v4l2_err(&sdev->sd, "Could not request IRQ\n");
			goto free_sdev;
		}
		v4l2_dbg(1, debug, &sdev->sd, "IRQ requested.\n");
	} else {
		v4l2_warn(&sdev->sd, "IRQ not configured. Using timeouts.\n");
	}

	rval = si4713_initialize(sdev);
	if (rval < 0) {
		v4l2_err(&sdev->sd, "Failed to probe device information.\n");
		goto free_irq;
	}

	return 0;

free_irq:
	if (client->irq)
		free_irq(client->irq, sdev);
free_sdev:
	kfree(sdev);
exit:
	return rval;
}