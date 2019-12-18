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
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 

__attribute__((used)) static bool ivch_write(struct intel_dvo_device *dvo, int addr, uint16_t data)
{
	struct ivch_priv *priv = dvo->dev_priv;
	struct i2c_adapter *adapter = dvo->i2c_bus;
	u8 out_buf[3];
	struct i2c_msg msg = {
		.addr = dvo->slave_addr,
		.flags = 0,
		.len = 3,
		.buf = out_buf,
	};

	out_buf[0] = addr;
	out_buf[1] = data & 0xff;
	out_buf[2] = data >> 8;

	if (i2c_transfer(adapter, &msg, 1) == 1)
		return true;

	if (!priv->quiet) {
		DRM_DEBUG_KMS("Unable to write register 0x%02x to %s:%d.\n",
			  addr, adapter->name, dvo->slave_addr);
	}

	return false;
}