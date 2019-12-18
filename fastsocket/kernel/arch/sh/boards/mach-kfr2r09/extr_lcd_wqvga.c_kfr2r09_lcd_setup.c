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
struct sh_mobile_lcdc_sys_bus_ops {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIO_PTE4 ; 
 int /*<<< orphan*/  GPIO_PTF4 ; 
 int /*<<< orphan*/  display_on (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int read_device_code (void*,struct sh_mobile_lcdc_sys_bus_ops*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int kfr2r09_lcd_setup(void *board_data, void *sohandle,
		      struct sh_mobile_lcdc_sys_bus_ops *so)
{
	/* power on */
	gpio_set_value(GPIO_PTF4, 0);  /* PROTECT/ -> L */
	gpio_set_value(GPIO_PTE4, 0);  /* LCD_RST/ -> L */
	gpio_set_value(GPIO_PTF4, 1);  /* PROTECT/ -> H */
	udelay(1100);
	gpio_set_value(GPIO_PTE4, 1);  /* LCD_RST/ -> H */
	udelay(10);
	gpio_set_value(GPIO_PTF4, 0);  /* PROTECT/ -> L */
	mdelay(20);

	if (read_device_code(sohandle, so) != 0x01221517)
		return -ENODEV;

	pr_info("KFR2R09 WQVGA LCD Module detected.\n");

	display_on(sohandle, so);
	return 0;
}