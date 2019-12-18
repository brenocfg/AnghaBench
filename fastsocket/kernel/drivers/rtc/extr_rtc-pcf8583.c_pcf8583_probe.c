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
struct pcf8583 {int /*<<< orphan*/  rtc; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf8583*) ; 
 int /*<<< orphan*/  kfree (struct pcf8583*) ; 
 struct pcf8583* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ pcf8583_driver ; 
 int /*<<< orphan*/  pcf8583_rtc_ops ; 
 int /*<<< orphan*/  rtc_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf8583_probe(struct i2c_client *client,
				const struct i2c_device_id *id)
{
	struct pcf8583 *pcf8583;
	int err;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	pcf8583 = kzalloc(sizeof(struct pcf8583), GFP_KERNEL);
	if (!pcf8583)
		return -ENOMEM;

	pcf8583->rtc = rtc_device_register(pcf8583_driver.driver.name,
			&client->dev, &pcf8583_rtc_ops, THIS_MODULE);

	if (IS_ERR(pcf8583->rtc)) {
		err = PTR_ERR(pcf8583->rtc);
		goto exit_kfree;
	}

	i2c_set_clientdata(client, pcf8583);
	return 0;

exit_kfree:
	kfree(pcf8583);
	return err;
}