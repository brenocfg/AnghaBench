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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDEBUG (int,int /*<<< orphan*/ *,char*,unsigned int) ; 
 int ENOIOCTLCMD ; 
#define  OVCAMCHIP_CMD_G_CTRL 130 
#define  OVCAMCHIP_CMD_S_CTRL 129 
#define  OVCAMCHIP_CMD_S_MODE 128 
 int ov7x20_get_v4l1_control (struct i2c_client*,void*) ; 
 int ov7x20_set_v4l1_control (struct i2c_client*,void*) ; 
 int ov7x20_set_window (struct i2c_client*,void*) ; 

__attribute__((used)) static int ov7x20_command(struct i2c_client *c, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case OVCAMCHIP_CMD_S_CTRL:
		return ov7x20_set_v4l1_control(c, arg);
	case OVCAMCHIP_CMD_G_CTRL:
		return ov7x20_get_v4l1_control(c, arg);
	case OVCAMCHIP_CMD_S_MODE:
		return ov7x20_set_window(c, arg);
	default:
		DDEBUG(2, &c->dev, "command not supported: %d", cmd);
		return -ENOIOCTLCMD;
	}
}