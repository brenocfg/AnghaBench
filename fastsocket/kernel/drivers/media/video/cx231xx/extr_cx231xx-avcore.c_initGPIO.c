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
typedef  int u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_MODE_SET ; 
 int /*<<< orphan*/  GBULK_BIT_EN ; 
 int /*<<< orphan*/  cx231xx_capture_start (struct cx231xx*,int,int) ; 
 int /*<<< orphan*/  cx231xx_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_mode_register (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx231xx_send_gpio_cmd (struct cx231xx*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verve_read_byte (struct cx231xx*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verve_write_byte (struct cx231xx*,int,int) ; 

void initGPIO(struct cx231xx *dev)
{
	u32 _gpio_direction = 0;
	u32 value = 0;
	u8 val = 0;

	_gpio_direction = _gpio_direction & 0xFC0003FF;
	_gpio_direction = _gpio_direction | 0x03FDFC00;
	cx231xx_send_gpio_cmd(dev, _gpio_direction, (u8 *)&value, 4, 0, 0);

	verve_read_byte(dev, 0x07, &val);
	cx231xx_info(" verve_read_byte address0x07=0x%x\n", val);
	verve_write_byte(dev, 0x07, 0xF4);
	verve_read_byte(dev, 0x07, &val);
	cx231xx_info(" verve_read_byte address0x07=0x%x\n", val);

	cx231xx_capture_start(dev, 1, 2);

	cx231xx_mode_register(dev, EP_MODE_SET, 0x0500FE00);
	cx231xx_mode_register(dev, GBULK_BIT_EN, 0xFFFDFFFF);

}