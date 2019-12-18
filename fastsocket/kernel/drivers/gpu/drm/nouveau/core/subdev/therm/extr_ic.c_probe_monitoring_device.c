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
struct nvbios_therm_sensor {int /*<<< orphan*/  offset_constant; } ;
struct nouveau_therm_priv {struct i2c_client* ic; struct nvbios_therm_sensor bios_sensor; } ;
struct nouveau_i2c_port {int /*<<< orphan*/  adapter; } ;
struct i2c_client {TYPE_1__* driver; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ (* detect ) (struct i2c_client*,int,struct i2c_board_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_MODULE_PREFIX ; 
 struct i2c_client* i2c_new_device (int /*<<< orphan*/ *,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 scalar_t__ nouveau_therm (struct nouveau_i2c_port*) ; 
 int /*<<< orphan*/  nv_info (struct nouveau_therm_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct i2c_client*,int,struct i2c_board_info*) ; 

__attribute__((used)) static bool
probe_monitoring_device(struct nouveau_i2c_port *i2c,
			struct i2c_board_info *info)
{
	struct nouveau_therm_priv *priv = (void *)nouveau_therm(i2c);
	struct nvbios_therm_sensor *sensor = &priv->bios_sensor;
	struct i2c_client *client;

	request_module("%s%s", I2C_MODULE_PREFIX, info->type);

	client = i2c_new_device(&i2c->adapter, info);
	if (!client)
		return false;

	if (!client->driver || client->driver->detect(client, -1, info)) {
		i2c_unregister_device(client);
		return false;
	}

	nv_info(priv,
		"Found an %s at address 0x%x (controlled by lm_sensors, "
		"temp offset %+i C)\n",
		info->type, info->addr, sensor->offset_constant);
	priv->ic = client;

	return true;
}