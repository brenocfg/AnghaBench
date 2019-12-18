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
typedef  int /*<<< orphan*/  u32 ;
struct IR_i2c {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 int EINVAL ; 
 int get_key_haup_common (struct IR_i2c*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int get_key_haup_xvr(struct IR_i2c *ir, u32 *ir_key, u32 *ir_raw)
{
	int ret;
	unsigned char buf[1] = { 0 };

	/*
	 * This is the same apparent "are you ready?" poll command observed
	 * watching Windows driver traffic and implemented in lirc_zilog. With
	 * this added, we get far saner remote behavior with z8 chips on usb
	 * connected devices, even with the default polling interval of 100ms.
	 */
	ret = i2c_master_send(ir->c, buf, 1);
	if (ret != 1)
		return (ret < 0) ? ret : -EINVAL;

	return get_key_haup_common (ir, ir_key, ir_raw, 6, 3);
}