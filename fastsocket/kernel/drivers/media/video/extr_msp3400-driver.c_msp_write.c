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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msp_debug ; 
 int /*<<< orphan*/  msp_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int,int) ; 
 int /*<<< orphan*/  v4l_warn (struct i2c_client*,char*,...) ; 

__attribute__((used)) static int msp_write(struct i2c_client *client, int dev, int addr, int val)
{
	int err;
	u8 buffer[5];

	buffer[0] = dev;
	buffer[1] = addr >> 8;
	buffer[2] = addr &  0xff;
	buffer[3] = val  >> 8;
	buffer[4] = val  &  0xff;

	v4l_dbg(3, msp_debug, client, "msp_write(0x%x, 0x%x, 0x%x)\n",
			dev, addr, val);
	for (err = 0; err < 3; err++) {
		if (i2c_master_send(client, buffer, 5) == 5)
			break;
		v4l_warn(client, "I/O error #%d (write 0x%02x/0x%02x)\n", err,
		       dev, addr);
		schedule_timeout_interruptible(msecs_to_jiffies(10));
	}
	if (err == 3) {
		v4l_warn(client, "resetting chip, sound will go off.\n");
		msp_reset(client);
		return -1;
	}
	return 0;
}