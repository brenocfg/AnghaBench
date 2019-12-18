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
struct intel_dvo_device {int /*<<< orphan*/  i2c_bus; int /*<<< orphan*/  slave_addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static bool ch7017_read(struct intel_dvo_device *dvo, u8 addr, u8 *val)
{
	struct i2c_msg msgs[] = {
		{
			.addr = dvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		},
		{
			.addr = dvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = val,
		}
	};
	return i2c_transfer(dvo->i2c_bus, msgs, 2) == 2;
}