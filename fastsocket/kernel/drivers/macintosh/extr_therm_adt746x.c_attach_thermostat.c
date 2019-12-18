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
struct i2c_client {int /*<<< orphan*/  detected; } ;
struct i2c_board_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  type; } ;
struct i2c_adapter {scalar_t__ name; } ;
struct TYPE_2__ {int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 unsigned long simple_strtoul (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  therm_address ; 
 unsigned long therm_bus ; 
 TYPE_1__ thermostat_driver ; 

__attribute__((used)) static int
attach_thermostat(struct i2c_adapter *adapter)
{
	unsigned long bus_no;
	struct i2c_board_info info;
	struct i2c_client *client;

	if (strncmp(adapter->name, "uni-n", 5))
		return -ENODEV;
	bus_no = simple_strtoul(adapter->name + 6, NULL, 10);
	if (bus_no != therm_bus)
		return -ENODEV;

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, "therm_adt746x", I2C_NAME_SIZE);
	info.addr = therm_address;
	client = i2c_new_device(adapter, &info);
	if (!client)
		return -ENODEV;

	/*
	 * Let i2c-core delete that device on driver removal.
	 * This is safe because i2c-core holds the core_lock mutex for us.
	 */
	list_add_tail(&client->detected, &thermostat_driver.clients);
	return 0;
}