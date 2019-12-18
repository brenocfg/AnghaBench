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
 unsigned char const W9966_I2C_R_CLOCK ; 
 unsigned char w9966_rReg (struct w9966_dev*,int) ; 

__attribute__((used)) static inline int w9966_i2c_getscl(struct w9966_dev* cam)
{
	const unsigned char state = w9966_rReg(cam, 0x18);
	return ((state & W9966_I2C_R_CLOCK) > 0);
}