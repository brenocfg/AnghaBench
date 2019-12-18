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
typedef  int /*<<< orphan*/  u8 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRT_SET_REGISTER ; 
 int /*<<< orphan*/  cx231xx_capture_start (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx231xx_write_ctrl_reg (struct cx231xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verve_write_byte (struct cx231xx*,int,int) ; 

void uninitGPIO(struct cx231xx *dev)
{
	u8 value[4] = { 0, 0, 0, 0 };

	cx231xx_capture_start(dev, 0, 2);
	verve_write_byte(dev, 0x07, 0x14);
	cx231xx_write_ctrl_reg(dev, VRT_SET_REGISTER,
			0x68, value, 4);
}