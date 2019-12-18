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
 int ADT7473_CFG1_READY ; 
 int ADT7473_CFG1_START ; 
 int /*<<< orphan*/  ADT7473_REG_CFG1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adt7473_init_client(struct i2c_client *client)
{
	int reg = i2c_smbus_read_byte_data(client, ADT7473_REG_CFG1);

	if (!(reg & ADT7473_CFG1_READY)) {
		dev_err(&client->dev, "Chip not ready.\n");
	} else {
		/* start monitoring */
		i2c_smbus_write_byte_data(client, ADT7473_REG_CFG1,
					  reg | ADT7473_CFG1_START);
	}
}