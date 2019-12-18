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
struct TYPE_4__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct wf_lm75_sensor {TYPE_2__ sens; struct i2c_client* i2c; int /*<<< orphan*/  ds1775; scalar_t__ inited; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wf_lm75_sensor*) ; 
 int /*<<< orphan*/  kfree (struct wf_lm75_sensor*) ; 
 struct wf_lm75_sensor* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wf_lm75_ops ; 
 int wf_register_sensor (TYPE_2__*) ; 

__attribute__((used)) static int wf_lm75_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct wf_lm75_sensor *lm;
	int rc;

	lm = kzalloc(sizeof(struct wf_lm75_sensor), GFP_KERNEL);
	if (lm == NULL)
		return -ENODEV;

	lm->inited = 0;
	lm->ds1775 = id->driver_data;
	lm->i2c = client;
	lm->sens.name = client->dev.platform_data;
	lm->sens.ops = &wf_lm75_ops;
	i2c_set_clientdata(client, lm);

	rc = wf_register_sensor(&lm->sens);
	if (rc) {
		i2c_set_clientdata(client, NULL);
		kfree(lm);
	}

	return rc;
}