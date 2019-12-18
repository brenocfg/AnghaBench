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
typedef  int u32 ;
struct synaptics_ts_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_read (struct synaptics_ts_data*,int,char*) ; 
 int i2c_set (struct synaptics_ts_data*,int,int,char*) ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

__attribute__((used)) static int detect(struct synaptics_ts_data *ts, u32 *panel_version)
{
	int ret;
	int retry = 10;

	ret = i2c_set(ts, 0xf4, 0x01, "reset device");

	while (retry-- > 0) {
		ret = i2c_smbus_read_byte_data(ts->client, 0xe4);
		if (ret >= 0)
			break;
		msleep(100);
	}
	if (ret < 0) {
		pr_err("i2c_smbus_read_byte_data failed\n");
		return ret;
	}

	*panel_version = ret << 8;
	ret = i2c_read(ts, 0xe5, "product minor");
	if (ret < 0)
		return ret;
	*panel_version |= ret;

	ret = i2c_read(ts, 0xe3, "property");
	if (ret < 0)
		return ret;

	pr_info("synaptics: version %x, product property %x\n",
		*panel_version, ret);
	return 0;
}