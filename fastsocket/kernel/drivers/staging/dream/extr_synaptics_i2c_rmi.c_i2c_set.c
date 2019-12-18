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
typedef  int /*<<< orphan*/  u8 ;
struct synaptics_ts_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static int i2c_set(struct synaptics_ts_data *ts, u8 reg, u8 val, char *msg)
{
	int ret = i2c_smbus_write_byte_data(ts->client, reg, val);
	if (ret < 0)
		pr_err("i2c_smbus_write_byte_data failed (%s)\n", msg);
	return ret;
}