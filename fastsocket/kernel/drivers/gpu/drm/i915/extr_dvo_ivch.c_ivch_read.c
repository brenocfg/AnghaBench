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
typedef  int uint16_t ;
typedef  int u8 ;
struct ivch_priv {int /*<<< orphan*/  quiet; } ;
struct intel_dvo_device {int /*<<< orphan*/  slave_addr; struct i2c_adapter* i2c_bus; struct ivch_priv* dev_priv; } ;
struct i2c_msg {int flags; int len; int* buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int I2C_M_NOSTART ; 
 int I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static bool ivch_read(struct intel_dvo_device *dvo, int addr, uint16_t *data)
{
	struct ivch_priv *priv = dvo->dev_priv;
	struct i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[1];
	u8 in_buf[2];

	struct i2c_msg msgs[] = {
		{
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 0,
		},
		{
			.addr = 0,
			.flags = I2C_M_NOSTART,
			.len = 1,
			.buf = out_buf,
		},
		{
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD | I2C_M_NOSTART,
			.len = 2,
			.buf = in_buf,
		}
	};

	out_buf[0] = addr;

	if (i2c_transfer(adapter, msgs, 3) == 3) {
		*data = (in_buf[1] << 8) | in_buf[0];
		return true;
	};

	if (!priv->quiet) {
		DRM_DEBUG_KMS("Unable to read register 0x%02x from "
				"%s:%02x.\n",
			  addr, adapter->name, dvo->slave_addr);
	}
	return false;
}