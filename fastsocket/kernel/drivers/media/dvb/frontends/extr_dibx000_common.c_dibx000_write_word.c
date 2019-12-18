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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dibx000_i2c_master {int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  i2c_addr; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int dibx000_write_word(struct dibx000_i2c_master *mst, u16 reg, u16 val)
{
	u8 b[4] = {
		(reg >> 8) & 0xff, reg & 0xff,
		(val >> 8) & 0xff, val & 0xff,
	};
	struct i2c_msg msg = {
		.addr = mst->i2c_addr,.flags = 0,.buf = b,.len = 4
	};
	return i2c_transfer(mst->i2c_adap, &msg, 1) != 1 ? -EREMOTEIO : 0;
}