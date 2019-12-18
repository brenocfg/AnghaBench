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
struct tw9910_scale_ctrl {int vscale; int hscale; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSCALE_LO ; 
 int /*<<< orphan*/  SCALE_HI ; 
 int /*<<< orphan*/  VSCALE_LO ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tw9910_set_scale(struct i2c_client *client,
			    const struct tw9910_scale_ctrl *scale)
{
	int ret;

	ret = i2c_smbus_write_byte_data(client, SCALE_HI,
					(scale->vscale & 0x0F00) >> 4 |
					(scale->hscale & 0x0F00) >> 8);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, HSCALE_LO,
					scale->hscale & 0x00FF);
	if (ret < 0)
		return ret;

	ret = i2c_smbus_write_byte_data(client, VSCALE_LO,
					scale->vscale & 0x00FF);

	return ret;
}