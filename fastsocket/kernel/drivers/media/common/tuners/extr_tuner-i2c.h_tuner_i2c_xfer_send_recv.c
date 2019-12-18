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
struct tuner_i2c_props {int /*<<< orphan*/  adap; int /*<<< orphan*/  addr; } ;
struct i2c_msg {char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static inline int tuner_i2c_xfer_send_recv(struct tuner_i2c_props *props,
					   char *obuf, int olen,
					   char *ibuf, int ilen)
{
	struct i2c_msg msg[2] = { { .addr = props->addr, .flags = 0,
				    .buf = obuf, .len = olen },
				  { .addr = props->addr, .flags = I2C_M_RD,
				    .buf = ibuf, .len = ilen } };
	int ret = i2c_transfer(props->adap, msg, 2);

	return (ret == 2) ? ilen : ret;
}