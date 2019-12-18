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
typedef  scalar_t__ u16 ;
struct em28xx {scalar_t__ reg_gpo_num; char reg_gpo; scalar_t__ reg_gpio_num; char reg_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_REQ_GET_STATUS ; 
 int em28xx_write_regs_req (struct em28xx*,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 

int em28xx_write_regs(struct em28xx *dev, u16 reg, char *buf, int len)
{
	int rc;

	rc = em28xx_write_regs_req(dev, USB_REQ_GET_STATUS, reg, buf, len);

	/* Stores GPO/GPIO values at the cache, if changed
	   Only write values should be stored, since input on a GPIO
	   register will return the input bits.
	   Not sure what happens on reading GPO register.
	 */
	if (rc >= 0) {
		if (reg == dev->reg_gpo_num)
			dev->reg_gpo = buf[0];
		else if (reg == dev->reg_gpio_num)
			dev->reg_gpio = buf[0];
	}

	return rc;
}