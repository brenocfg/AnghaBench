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
 int PROSAVAGE_I2C_SCL_IN ; 
 int VGArCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prosavage_gpio_getscl(void* data)
{
	struct savagefb_i2c_chan *chan = data;

	return (VGArCR(chan->reg, chan->par) & PROSAVAGE_I2C_SCL_IN) ? 1 : 0;
}