#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct twl4030_platform_data {scalar_t__ irq_base; scalar_t__ irq_end; scalar_t__ power; } ;
struct twl4030_client {int /*<<< orphan*/  xfer_lock; struct i2c_client* client; scalar_t__ address; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {struct twl4030_platform_data* platform_data; } ;
struct i2c_client {scalar_t__ irq; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/  adapter; scalar_t__ addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 unsigned int TWL4030_NUM_SLAVES ; 
 int add_children (struct twl4030_platform_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocks_init (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,unsigned int) ; 
 scalar_t__ i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_dummy (int /*<<< orphan*/ ,scalar_t__) ; 
 int inuse ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct twl4030_client* twl4030_modules ; 
 int /*<<< orphan*/  twl4030_power_init (scalar_t__) ; 
 int /*<<< orphan*/  twl4030_remove (struct i2c_client*) ; 
 scalar_t__ twl_has_power () ; 
 int twl_init_irq (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
twl4030_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int				status;
	unsigned			i;
	struct twl4030_platform_data	*pdata = client->dev.platform_data;

	if (!pdata) {
		dev_dbg(&client->dev, "no platform data?\n");
		return -EINVAL;
	}

	if (i2c_check_functionality(client->adapter, I2C_FUNC_I2C) == 0) {
		dev_dbg(&client->dev, "can't talk I2C?\n");
		return -EIO;
	}

	if (inuse) {
		dev_dbg(&client->dev, "driver is already in use\n");
		return -EBUSY;
	}

	for (i = 0; i < TWL4030_NUM_SLAVES; i++) {
		struct twl4030_client	*twl = &twl4030_modules[i];

		twl->address = client->addr + i;
		if (i == 0)
			twl->client = client;
		else {
			twl->client = i2c_new_dummy(client->adapter,
					twl->address);
			if (!twl->client) {
				dev_err(&client->dev,
					"can't attach client %d\n", i);
				status = -ENOMEM;
				goto fail;
			}
			strlcpy(twl->client->name, id->name,
					sizeof(twl->client->name));
		}
		mutex_init(&twl->xfer_lock);
	}
	inuse = true;

	/* setup clock framework */
	clocks_init(&client->dev);

	/* load power event scripts */
	if (twl_has_power() && pdata->power)
		twl4030_power_init(pdata->power);

	/* Maybe init the T2 Interrupt subsystem */
	if (client->irq
			&& pdata->irq_base
			&& pdata->irq_end > pdata->irq_base) {
		status = twl_init_irq(client->irq, pdata->irq_base, pdata->irq_end);
		if (status < 0)
			goto fail;
	}

	status = add_children(pdata, id->driver_data);
fail:
	if (status < 0)
		twl4030_remove(client);
	return status;
}