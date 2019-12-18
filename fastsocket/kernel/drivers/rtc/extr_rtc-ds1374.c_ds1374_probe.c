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
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct ds1374 {int /*<<< orphan*/  rtc; int /*<<< orphan*/  mutex; int /*<<< orphan*/  work; struct i2c_client* client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ds1374_check_rtc_status (struct i2c_client*) ; 
 int /*<<< orphan*/  ds1374_irq ; 
 int /*<<< orphan*/  ds1374_rtc_ops ; 
 int /*<<< orphan*/  ds1374_work ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ds1374*) ; 
 int /*<<< orphan*/  kfree (struct ds1374*) ; 
 struct ds1374* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i2c_client*) ; 
 int /*<<< orphan*/  rtc_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1374_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct ds1374 *ds1374;
	int ret;

	ds1374 = kzalloc(sizeof(struct ds1374), GFP_KERNEL);
	if (!ds1374)
		return -ENOMEM;

	ds1374->client = client;
	i2c_set_clientdata(client, ds1374);

	INIT_WORK(&ds1374->work, ds1374_work);
	mutex_init(&ds1374->mutex);

	ret = ds1374_check_rtc_status(client);
	if (ret)
		goto out_free;

	if (client->irq > 0) {
		ret = request_irq(client->irq, ds1374_irq, 0,
		                  "ds1374", client);
		if (ret) {
			dev_err(&client->dev, "unable to request IRQ\n");
			goto out_free;
		}
	}

	ds1374->rtc = rtc_device_register(client->name, &client->dev,
	                                  &ds1374_rtc_ops, THIS_MODULE);
	if (IS_ERR(ds1374->rtc)) {
		ret = PTR_ERR(ds1374->rtc);
		dev_err(&client->dev, "unable to register the class device\n");
		goto out_irq;
	}

	return 0;

out_irq:
	if (client->irq > 0)
		free_irq(client->irq, client);

out_free:
	i2c_set_clientdata(client, NULL);
	kfree(ds1374);
	return ret;
}