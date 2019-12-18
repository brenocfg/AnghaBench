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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  nforce2_access_channel (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*,int) ; 

__attribute__((used)) static s32 nforce2_access_virt4(struct i2c_adapter *adap, u16 addr,
				unsigned short flags, char read_write,
				u8 command, int size,
				union i2c_smbus_data *data)
{
	/* CPU3: channel 4 enabled */
	return nforce2_access_channel(adap, addr, flags, read_write, command,
				      size, data, 0x10);
}