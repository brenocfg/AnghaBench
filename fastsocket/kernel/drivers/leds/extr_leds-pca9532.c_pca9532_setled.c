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
struct pca9532_led {int state; int /*<<< orphan*/  id; struct i2c_client* client; } ;
struct pca9532_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int LED_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_REG (int /*<<< orphan*/ ) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 char i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pca9532_setled(struct pca9532_led *led)
{
	struct i2c_client *client = led->client;
	struct pca9532_data *data = i2c_get_clientdata(client);
	char reg;

	mutex_lock(&data->update_lock);
	reg = i2c_smbus_read_byte_data(client, LED_REG(led->id));
	/* zero led bits */
	reg = reg & ~(0x3<<LED_NUM(led->id)*2);
	/* set the new value */
	reg = reg | (led->state << LED_NUM(led->id)*2);
	i2c_smbus_write_byte_data(client, LED_REG(led->id), reg);
	mutex_unlock(&data->update_lock);
}