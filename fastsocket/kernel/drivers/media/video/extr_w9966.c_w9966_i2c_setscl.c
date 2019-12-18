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
struct w9966_dev {int /*<<< orphan*/  i2c_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  W9966_I2C_W_CLOCK ; 
 int jiffies ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w9966_i2c_getscl (struct w9966_dev*) ; 
 int /*<<< orphan*/  w9966_wReg (struct w9966_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int w9966_i2c_setscl(struct w9966_dev* cam, int state)
{
	unsigned long timeout;

	if (state)
		cam->i2c_state |= W9966_I2C_W_CLOCK;
	else
		cam->i2c_state &= ~W9966_I2C_W_CLOCK;

	w9966_wReg(cam, 0x18, cam->i2c_state);
	udelay(5);

	// we go to high, we also expect the peripheral to ack.
	if (state) {
		timeout = jiffies + 100;
		while (!w9966_i2c_getscl(cam)) {
			if (time_after(jiffies, timeout))
				return -1;
		}
	}
	return 0;
}