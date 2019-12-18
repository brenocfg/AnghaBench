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
typedef  scalar_t__ u8 ;
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int MAX_RETRIES ; 
 int /*<<< orphan*/  STK_ERROR (char*,int) ; 
 int /*<<< orphan*/  STK_IIC_OP ; 
 scalar_t__ STK_IIC_OP_RX ; 
 int /*<<< orphan*/  STK_IIC_RX_INDEX ; 
 int /*<<< orphan*/  STK_IIC_RX_VALUE ; 
 int /*<<< orphan*/  STK_IIC_STAT ; 
 int STK_IIC_STAT_RX_OK ; 
 scalar_t__ stk_camera_read_reg (struct stk_camera*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stk_camera_write_reg (struct stk_camera*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int stk_sensor_inb(struct stk_camera *dev, u8 reg, u8 *val)
{
	int i = 0;
	int tmpval = 0;

	if (stk_camera_write_reg(dev, STK_IIC_RX_INDEX, reg))
		return 1;
	if (stk_camera_write_reg(dev, STK_IIC_OP, STK_IIC_OP_RX))
		return 1;
	do {
		if (stk_camera_read_reg(dev, STK_IIC_STAT, &tmpval))
			return 1;
		i++;
	} while (tmpval == 0 && i < MAX_RETRIES);
	if (tmpval != STK_IIC_STAT_RX_OK) {
		if (tmpval)
			STK_ERROR("stk_sensor_inb failed, status=0x%02x\n",
				tmpval);
		return 1;
	}

	if (stk_camera_read_reg(dev, STK_IIC_RX_VALUE, &tmpval))
		return 1;

	*val = (u8) tmpval;
	return 0;
}