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
typedef  int u8 ;
struct w83791d_data {TYPE_1__** lm75; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  W83791D_REG_I2C_SUBADDR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int* force_subclients ; 
 int i2c_adapter_id (struct i2c_adapter*) ; 
 struct w83791d_data* i2c_get_clientdata (struct i2c_client*) ; 
 void* i2c_new_dummy (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_unregister_device (TYPE_1__*) ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83791d_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w83791d_detect_subclients(struct i2c_client *client)
{
	struct i2c_adapter *adapter = client->adapter;
	struct w83791d_data *data = i2c_get_clientdata(client);
	int address = client->addr;
	int i, id, err;
	u8 val;

	id = i2c_adapter_id(adapter);
	if (force_subclients[0] == id && force_subclients[1] == address) {
		for (i = 2; i <= 3; i++) {
			if (force_subclients[i] < 0x48 ||
			    force_subclients[i] > 0x4f) {
				dev_err(&client->dev,
					"invalid subclient "
					"address %d; must be 0x48-0x4f\n",
					force_subclients[i]);
				err = -ENODEV;
				goto error_sc_0;
			}
		}
		w83791d_write(client, W83791D_REG_I2C_SUBADDR,
					(force_subclients[2] & 0x07) |
					((force_subclients[3] & 0x07) << 4));
	}

	val = w83791d_read(client, W83791D_REG_I2C_SUBADDR);
	if (!(val & 0x08)) {
		data->lm75[0] = i2c_new_dummy(adapter, 0x48 + (val & 0x7));
	}
	if (!(val & 0x80)) {
		if ((data->lm75[0] != NULL) &&
				((val & 0x7) == ((val >> 4) & 0x7))) {
			dev_err(&client->dev,
				"duplicate addresses 0x%x, "
				"use force_subclient\n",
				data->lm75[0]->addr);
			err = -ENODEV;
			goto error_sc_1;
		}
		data->lm75[1] = i2c_new_dummy(adapter,
					      0x48 + ((val >> 4) & 0x7));
	}

	return 0;

/* Undo inits in case of errors */

error_sc_1:
	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
error_sc_0:
	return err;
}