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
typedef  int u8 ;
struct tda10021_state {int /*<<< orphan*/  i2c; TYPE_1__* config; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int* tda10021_inittab ; 

__attribute__((used)) static int lock_tuner(struct tda10021_state* state)
{
	u8 buf[2] = { 0x0f, tda10021_inittab[0x0f] | 0x80 };
	struct i2c_msg msg = {.addr=state->config->demod_address, .flags=0, .buf=buf, .len=2};

	if(i2c_transfer(state->i2c, &msg, 1) != 1)
	{
		printk("tda10021: lock tuner fails\n");
		return -EREMOTEIO;
	}
	return 0;
}