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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int retries; int /*<<< orphan*/  bus_lock; scalar_t__ timeout; TYPE_1__* algo; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* smbus_xfer ) (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 unsigned short I2C_CLIENT_PEC ; 
 unsigned short I2C_M_TEN ; 
 int /*<<< orphan*/  i2c_smbus_xfer_emulated (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

s32 i2c_smbus_xfer(struct i2c_adapter *adapter, u16 addr, unsigned short flags,
		   char read_write, u8 command, int protocol,
		   union i2c_smbus_data *data)
{
	unsigned long orig_jiffies;
	int try;
	s32 res;

	flags &= I2C_M_TEN | I2C_CLIENT_PEC;

	if (adapter->algo->smbus_xfer) {
		mutex_lock(&adapter->bus_lock);

		/* Retry automatically on arbitration loss */
		orig_jiffies = jiffies;
		for (res = 0, try = 0; try <= adapter->retries; try++) {
			res = adapter->algo->smbus_xfer(adapter, addr, flags,
							read_write, command,
							protocol, data);
			if (res != -EAGAIN)
				break;
			if (time_after(jiffies,
				       orig_jiffies + adapter->timeout))
				break;
		}
		mutex_unlock(&adapter->bus_lock);
	} else
		res = i2c_smbus_xfer_emulated(adapter,addr,flags,read_write,
					      command, protocol, data);

	return res;
}