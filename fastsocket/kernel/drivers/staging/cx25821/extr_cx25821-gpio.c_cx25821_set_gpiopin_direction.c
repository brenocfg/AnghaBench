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
typedef  int u32 ;
struct cx25821_dev {int dummy; } ;

/* Variables and functions */
 int Clear_GPIO_Bit (int) ; 
 int GPIO_HI_OE ; 
 int GPIO_LO_OE ; 
 int Set_GPIO_Bit (int) ; 
 int cx_read (int) ; 
 int /*<<< orphan*/  cx_write (int,int) ; 

void cx25821_set_gpiopin_direction(struct cx25821_dev *dev,
				   int pin_number, int pin_logic_value)
{
	int bit = pin_number;
	u32 gpio_oe_reg = GPIO_LO_OE;
	u32 gpio_register = 0;
	u32 value = 0;

	// Check for valid pinNumber
	if (pin_number >= 47)
		return;

	if (pin_number > 31) {
		bit = pin_number - 31;
		gpio_oe_reg = GPIO_HI_OE;
	}
	// Here we will make sure that the GPIOs 0 and 1 are output. keep the rest as is
	gpio_register = cx_read(gpio_oe_reg);

	if (pin_logic_value == 1) {
		value = gpio_register | Set_GPIO_Bit(bit);
	} else {
		value = gpio_register & Clear_GPIO_Bit(bit);
	}

	cx_write(gpio_oe_reg, value);
}