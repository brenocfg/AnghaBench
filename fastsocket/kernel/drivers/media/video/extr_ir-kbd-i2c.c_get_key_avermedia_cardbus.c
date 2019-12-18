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
typedef  unsigned char u32 ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct IR_i2c {TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int get_key_avermedia_cardbus(struct IR_i2c *ir,
				     u32 *ir_key, u32 *ir_raw)
{
	unsigned char subaddr, key, keygroup;
	struct i2c_msg msg[] = { { .addr = ir->c->addr, .flags = 0,
				   .buf = &subaddr, .len = 1},
				 { .addr = ir->c->addr, .flags = I2C_M_RD,
				  .buf = &key, .len = 1} };
	subaddr = 0x0d;
	if (2 != i2c_transfer(ir->c->adapter, msg, 2)) {
		dprintk(1, "read error\n");
		return -EIO;
	}

	if (key == 0xff)
		return 0;

	subaddr = 0x0b;
	msg[1].buf = &keygroup;
	if (2 != i2c_transfer(ir->c->adapter, msg, 2)) {
		dprintk(1, "read error\n");
		return -EIO;
	}

	if (keygroup == 0xff)
		return 0;

	dprintk(1, "read key 0x%02x/0x%02x\n", key, keygroup);
	if (keygroup < 2 || keygroup > 3) {
		/* Only a warning */
		dprintk(1, "warning: invalid key group 0x%02x for key 0x%02x\n",
								keygroup, key);
	}
	key |= (keygroup & 1) << 6;

	*ir_key = key;
	*ir_raw = key;
	return 1;
}