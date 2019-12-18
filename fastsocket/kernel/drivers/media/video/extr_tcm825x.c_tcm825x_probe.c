#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct tcm825x_sensor {int /*<<< orphan*/ * v4l2_int_device; TYPE_3__ pix; struct i2c_client* i2c_client; TYPE_2__* platform_data; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {TYPE_2__* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* is_okay ) () ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 size_t QVGA ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_RGB565 ; 
 scalar_t__ i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tcm825x_sensor*) ; 
 int /*<<< orphan*/  stub1 () ; 
 struct tcm825x_sensor tcm825x ; 
 int /*<<< orphan*/  tcm825x_int_device ; 
 TYPE_4__* tcm825x_sizes ; 
 int v4l2_int_device_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcm825x_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct tcm825x_sensor *sensor = &tcm825x;
	int rval;

	if (i2c_get_clientdata(client))
		return -EBUSY;

	sensor->platform_data = client->dev.platform_data;

	if (sensor->platform_data == NULL
	    || !sensor->platform_data->is_okay())
		return -ENODEV;

	sensor->v4l2_int_device = &tcm825x_int_device;

	sensor->i2c_client = client;
	i2c_set_clientdata(client, sensor);

	/* Make the default capture format QVGA RGB565 */
	sensor->pix.width = tcm825x_sizes[QVGA].width;
	sensor->pix.height = tcm825x_sizes[QVGA].height;
	sensor->pix.pixelformat = V4L2_PIX_FMT_RGB565;

	rval = v4l2_int_device_register(sensor->v4l2_int_device);
	if (rval)
		i2c_set_clientdata(client, NULL);

	return rval;
}