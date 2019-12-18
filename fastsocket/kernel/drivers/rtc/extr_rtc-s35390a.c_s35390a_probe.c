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
struct s35390a {int twentyfourhour; struct i2c_client** client; int /*<<< orphan*/  rtc; } ;
struct rtc_time {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  adapter; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S35390A_CMD_STATUS1 ; 
 char S35390A_FLAG_24H ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* i2c_new_dummy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct s35390a*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct s35390a*) ; 
 struct s35390a* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int s35390a_disable_test_mode (struct s35390a*) ; 
 TYPE_2__ s35390a_driver ; 
 scalar_t__ s35390a_get_datetime (struct i2c_client*,struct rtc_time*) ; 
 int s35390a_get_reg (struct s35390a*,int /*<<< orphan*/ ,char*,int) ; 
 int s35390a_reset (struct s35390a*) ; 
 int /*<<< orphan*/  s35390a_rtc_ops ; 

__attribute__((used)) static int s35390a_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err;
	unsigned int i;
	struct s35390a *s35390a;
	struct rtc_time tm;
	char buf[1];

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		err = -ENODEV;
		goto exit;
	}

	s35390a = kzalloc(sizeof(struct s35390a), GFP_KERNEL);
	if (!s35390a) {
		err = -ENOMEM;
		goto exit;
	}

	s35390a->client[0] = client;
	i2c_set_clientdata(client, s35390a);

	/* This chip uses multiple addresses, use dummy devices for them */
	for (i = 1; i < 8; ++i) {
		s35390a->client[i] = i2c_new_dummy(client->adapter,
					client->addr + i);
		if (!s35390a->client[i]) {
			dev_err(&client->dev, "Address %02x unavailable\n",
						client->addr + i);
			err = -EBUSY;
			goto exit_dummy;
		}
	}

	err = s35390a_reset(s35390a);
	if (err < 0) {
		dev_err(&client->dev, "error resetting chip\n");
		goto exit_dummy;
	}

	err = s35390a_disable_test_mode(s35390a);
	if (err < 0) {
		dev_err(&client->dev, "error disabling test mode\n");
		goto exit_dummy;
	}

	err = s35390a_get_reg(s35390a, S35390A_CMD_STATUS1, buf, sizeof(buf));
	if (err < 0) {
		dev_err(&client->dev, "error checking 12/24 hour mode\n");
		goto exit_dummy;
	}
	if (buf[0] & S35390A_FLAG_24H)
		s35390a->twentyfourhour = 1;
	else
		s35390a->twentyfourhour = 0;

	if (s35390a_get_datetime(client, &tm) < 0)
		dev_warn(&client->dev, "clock needs to be set\n");

	s35390a->rtc = rtc_device_register(s35390a_driver.driver.name,
				&client->dev, &s35390a_rtc_ops, THIS_MODULE);

	if (IS_ERR(s35390a->rtc)) {
		err = PTR_ERR(s35390a->rtc);
		goto exit_dummy;
	}
	return 0;

exit_dummy:
	for (i = 1; i < 8; ++i)
		if (s35390a->client[i])
			i2c_unregister_device(s35390a->client[i]);
	kfree(s35390a);
	i2c_set_clientdata(client, NULL);

exit:
	return err;
}