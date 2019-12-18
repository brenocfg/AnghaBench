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
struct ivtv {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_client {int dummy; } ;
struct i2c_board_info {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int I2C_CLIENT_END ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 struct i2c_client* i2c_new_probed_device (int /*<<< orphan*/ *,struct i2c_board_info*,unsigned short const*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct i2c_client *ivtv_i2c_new_ir_legacy(struct ivtv *itv)
{
	struct i2c_board_info info;
	/*
	 * The external IR receiver is at i2c address 0x34.
	 * The internal IR receiver is at i2c address 0x30.
	 *
	 * In theory, both can be fitted, and Hauppauge suggests an external
	 * overrides an internal.  That's why we probe 0x1a (~0x34) first. CB
	 *
	 * Some of these addresses we probe may collide with other i2c address
	 * allocations, so this function must be called after all other i2c
	 * devices we care about are registered.
	 */
	const unsigned short addr_list[] = {
		0x1a,	/* Hauppauge IR external - collides with WM8739 */
		0x18,	/* Hauppauge IR internal */
		I2C_CLIENT_END
	};

	memset(&info, 0, sizeof(struct i2c_board_info));
	strlcpy(info.type, "ir_video", I2C_NAME_SIZE);
	return i2c_new_probed_device(&itv->i2c_adap, &info, addr_list);
}