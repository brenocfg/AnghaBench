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
typedef  int u16 ;
struct i2c_msg {int len; int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/ * buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int I2C_M_RD ; 
 int i2c_algo_dp_aux_address (struct i2c_adapter*,int /*<<< orphan*/ ,int) ; 
 int i2c_algo_dp_aux_get_byte (struct i2c_adapter*,int /*<<< orphan*/ *) ; 
 int i2c_algo_dp_aux_put_byte (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_algo_dp_aux_stop (struct i2c_adapter*,int) ; 

__attribute__((used)) static int
i2c_algo_dp_aux_xfer(struct i2c_adapter *adapter,
		     struct i2c_msg *msgs,
		     int num)
{
	int ret = 0;
	bool reading = false;
	int m;
	int b;

	for (m = 0; m < num; m++) {
		u16 len = msgs[m].len;
		u8 *buf = msgs[m].buf;
		reading = (msgs[m].flags & I2C_M_RD) != 0;
		ret = i2c_algo_dp_aux_address(adapter, msgs[m].addr, reading);
		if (ret < 0)
			break;
		if (reading) {
			for (b = 0; b < len; b++) {
				ret = i2c_algo_dp_aux_get_byte(adapter, &buf[b]);
				if (ret < 0)
					break;
			}
		} else {
			for (b = 0; b < len; b++) {
				ret = i2c_algo_dp_aux_put_byte(adapter, buf[b]);
				if (ret < 0)
					break;
			}
		}
		if (ret < 0)
			break;
	}
	if (ret >= 0)
		ret = num;
	i2c_algo_dp_aux_stop(adapter, reading);
	DRM_DEBUG_KMS("dp_aux_xfer return %d\n", ret);
	return ret;
}