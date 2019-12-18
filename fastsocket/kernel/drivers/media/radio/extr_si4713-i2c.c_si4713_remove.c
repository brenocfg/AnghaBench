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
struct v4l2_subdev {int dummy; } ;
struct si4713_device {scalar_t__ power_state; } ;
struct i2c_client {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_DOWN ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct si4713_device*) ; 
 struct v4l2_subdev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct si4713_device*) ; 
 int /*<<< orphan*/  si4713_set_power_state (struct si4713_device*,int /*<<< orphan*/ ) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd = i2c_get_clientdata(client);
	struct si4713_device *sdev = to_si4713_device(sd);

	if (sdev->power_state)
		si4713_set_power_state(sdev, POWER_DOWN);

	if (client->irq > 0)
		free_irq(client->irq, sdev);

	v4l2_device_unregister_subdev(sd);

	kfree(sdev);

	return 0;
}