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
typedef  int /*<<< orphan*/  u32 ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Clear_GPIO_Bit (int) ; 
 int /*<<< orphan*/  GPIO_HI ; 
 int /*<<< orphan*/  GPIO_LO ; 
 int /*<<< orphan*/  Set_GPIO_Bit (int) ; 
 int /*<<< orphan*/  cx25821_set_gpiopin_direction (struct cx25821_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx25821_set_gpiopin_logicvalue(struct cx25821_dev *dev,
					   int pin_number, int pin_logic_value)
{
	int bit = pin_number;
	u32 gpio_reg = GPIO_LO;
	u32 value = 0;

	// Check for valid pinNumber
	if (pin_number >= 47)
		return;

	cx25821_set_gpiopin_direction(dev, pin_number, 0);	// change to output direction

	if (pin_number > 31) {
		bit = pin_number - 31;
		gpio_reg = GPIO_HI;
	}

	value = cx_read(gpio_reg);

	if (pin_logic_value == 0) {
		value &= Clear_GPIO_Bit(bit);
	} else {
		value |= Set_GPIO_Bit(bit);
	}

	cx_write(gpio_reg, value);
}