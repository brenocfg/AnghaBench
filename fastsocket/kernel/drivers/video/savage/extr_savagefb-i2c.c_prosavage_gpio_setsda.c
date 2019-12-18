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
struct savagefb_i2c_chan {int /*<<< orphan*/  par; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned int PROSAVAGE_I2C_ENAB ; 
 unsigned int PROSAVAGE_I2C_SDA_OUT ; 
 unsigned int VGArCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGAwCR (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prosavage_gpio_setsda(void* data, int val)
{
	struct savagefb_i2c_chan *chan = data;
	unsigned int r;

	r = VGArCR(chan->reg, chan->par);
	r |= PROSAVAGE_I2C_ENAB;
	if (val) {
		r |= PROSAVAGE_I2C_SDA_OUT;
	} else {
		r &= ~PROSAVAGE_I2C_SDA_OUT;
	}

	VGAwCR(chan->reg, r, chan->par);
}