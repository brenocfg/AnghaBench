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
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct tcm825x_sensor {TYPE_1__* i2c_client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int tcm825x_read_reg (TYPE_1__*,int) ; 

__attribute__((used)) static int ioctl_dev_init(struct v4l2_int_device *s)
{
	struct tcm825x_sensor *sensor = s->priv;
	int r;

	r = tcm825x_read_reg(sensor->i2c_client, 0x01);
	if (r < 0)
		return r;
	if (r == 0) {
		dev_err(&sensor->i2c_client->dev, "device not detected\n");
		return -EIO;
	}
	return 0;
}