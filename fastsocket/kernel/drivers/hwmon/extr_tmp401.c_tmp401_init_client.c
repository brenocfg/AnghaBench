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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMP401_CONFIG_READ ; 
 int TMP401_CONFIG_SHUTDOWN ; 
 int /*<<< orphan*/  TMP401_CONFIG_WRITE ; 
 int /*<<< orphan*/  TMP401_CONVERSION_RATE_WRITE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tmp401_init_client(struct i2c_client *client)
{
	int config, config_orig;

	/* Set the conversion rate to 2 Hz */
	i2c_smbus_write_byte_data(client, TMP401_CONVERSION_RATE_WRITE, 5);

	/* Start conversions (disable shutdown if necessary) */
	config = i2c_smbus_read_byte_data(client, TMP401_CONFIG_READ);
	if (config < 0) {
		dev_warn(&client->dev, "Initialization failed!\n");
		return;
	}

	config_orig = config;
	config &= ~TMP401_CONFIG_SHUTDOWN;

	if (config != config_orig)
		i2c_smbus_write_byte_data(client, TMP401_CONFIG_WRITE, config);
}