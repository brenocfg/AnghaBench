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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dibx000_i2c_master {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIBX000_I2C_INTERFACE_TUNER ; 
 int EIO ; 
 int /*<<< orphan*/  dibx000_i2c_gate_ctrl (struct dibx000_i2c_master*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dibx000_i2c_select_interface (struct dibx000_i2c_master*,int /*<<< orphan*/ ) ; 
 struct dibx000_i2c_master* i2c_get_adapdata (struct i2c_adapter*) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (struct i2c_msg*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memset (struct i2c_msg*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dibx000_i2c_gated_tuner_xfer(struct i2c_adapter *i2c_adap,
					struct i2c_msg msg[], int num)
{
	struct dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);
	struct i2c_msg m[2 + num];
	u8 tx_open[4], tx_close[4];

	memset(m, 0, sizeof(struct i2c_msg) * (2 + num));

	dibx000_i2c_select_interface(mst, DIBX000_I2C_INTERFACE_TUNER);

	dibx000_i2c_gate_ctrl(mst, tx_open, msg[0].addr, 1);
	m[0].addr = mst->i2c_addr;
	m[0].buf = tx_open;
	m[0].len = 4;

	memcpy(&m[1], msg, sizeof(struct i2c_msg) * num);

	dibx000_i2c_gate_ctrl(mst, tx_close, 0, 0);
	m[num + 1].addr = mst->i2c_addr;
	m[num + 1].buf = tx_close;
	m[num + 1].len = 4;

	return i2c_transfer(mst->i2c_adap, m, 2 + num) == 2 + num ? num : -EIO;
}