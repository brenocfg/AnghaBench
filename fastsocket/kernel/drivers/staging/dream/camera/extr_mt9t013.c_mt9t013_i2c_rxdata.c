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
struct i2c_msg {unsigned short addr; int len; unsigned char* buf; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 scalar_t__ i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 TYPE_1__* mt9t013_client ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mt9t013_i2c_rxdata(unsigned short saddr,
	unsigned char *rxdata, int length)
{
	struct i2c_msg msgs[] = {
	{
		.addr   = saddr,
		.flags = 0,
		.len   = 2,
		.buf   = rxdata,
	},
	{
		.addr  = saddr,
		.flags = I2C_M_RD,
		.len   = length,
		.buf   = rxdata,
	},
	};

	if (i2c_transfer(mt9t013_client->adapter, msgs, 2) < 0) {
		pr_err("mt9t013_i2c_rxdata failed!\n");
		return -EIO;
	}

	return 0;
}