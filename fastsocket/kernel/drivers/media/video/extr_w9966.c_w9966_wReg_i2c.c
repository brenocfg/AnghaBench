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
struct w9966_dev {int dummy; } ;

/* Variables and functions */
 int W9966_I2C_W_ID ; 
 int w9966_i2c_setscl (struct w9966_dev*,int) ; 
 int /*<<< orphan*/  w9966_i2c_setsda (struct w9966_dev*,int) ; 
 int w9966_i2c_wbyte (struct w9966_dev*,int) ; 

__attribute__((used)) static int w9966_wReg_i2c(struct w9966_dev* cam, int reg, int data)
{
	w9966_i2c_setsda(cam, 0);
	w9966_i2c_setscl(cam, 0);

	if (
		w9966_i2c_wbyte(cam, W9966_I2C_W_ID) == -1 ||
		w9966_i2c_wbyte(cam, reg) == -1 ||
		w9966_i2c_wbyte(cam, data) == -1
	)
		return -1;

	w9966_i2c_setsda(cam, 0);
	if (w9966_i2c_setscl(cam, 1) == -1)
		return -1;

	w9966_i2c_setsda(cam, 1);

	return 0;
}