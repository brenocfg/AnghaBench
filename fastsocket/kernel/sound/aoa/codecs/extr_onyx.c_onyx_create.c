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
struct i2c_client {TYPE_1__* driver; int /*<<< orphan*/  detected; } ;
struct i2c_board_info {int addr; struct device_node* platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int onyx_create(struct i2c_adapter *adapter,
		       struct device_node *node,
		       int addr)
{
	struct i2c_board_info info;
	struct i2c_client *client;

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, "aoa_codec_onyx", I2C_NAME_SIZE);
	info.addr = addr;
	info.platform_data = node;
	client = i2c_new_device(adapter, &info);
	if (!client)
		return -ENODEV;

	/*
	 * We know the driver is already loaded, so the device should be
	 * already bound. If not it means binding failed, which suggests
	 * the device doesn't really exist and should be deleted.
	 * Ideally this would be replaced by better checks _before_
	 * instantiating the device.
	 */
	if (!client->driver) {
		i2c_unregister_device(client);
		return -ENODEV;
	}

	/*
	 * Let i2c-core delete that device on driver removal.
	 * This is safe because i2c-core holds the core_lock mutex for us.
	 */
	list_add_tail(&client->detected, &client->driver->clients);
	return 0;
}