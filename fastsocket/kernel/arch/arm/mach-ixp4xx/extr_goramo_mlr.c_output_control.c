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

/* Variables and functions */
 int /*<<< orphan*/  GPIO_SCL ; 
 int /*<<< orphan*/  GPIO_SDA ; 
 int /*<<< orphan*/  IXP4XX_GPIO_OUT ; 
 int control_value ; 
 int /*<<< orphan*/  gpio_line_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_scl (int) ; 
 int /*<<< orphan*/  set_sda (int) ; 
 int /*<<< orphan*/  set_str (int) ; 

__attribute__((used)) static void output_control(void)
{
	int i;

	gpio_line_config(GPIO_SCL, IXP4XX_GPIO_OUT);
	gpio_line_config(GPIO_SDA, IXP4XX_GPIO_OUT);

	for (i = 0; i < 8; i++) {
		set_scl(0);
		set_sda(control_value & (0x80 >> i)); /* MSB first */
		set_scl(1);	/* active edge */
	}

	set_str(1);
	set_str(0);

	set_scl(0);
	set_sda(1);		/* Be ready for START */
	set_scl(1);
}