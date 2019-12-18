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
 int CX23417_GPIO_MASK ; 
 int cx231xx_send_gpio_cmd (struct cx231xx*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setITVCReg(struct cx231xx *dev, u32 gpio_direction, u32 value)
{
	int status = 0;
	u32 _gpio_direction = 0;

	_gpio_direction = _gpio_direction & CX23417_GPIO_MASK;
	_gpio_direction = _gpio_direction|gpio_direction;
	status = cx231xx_send_gpio_cmd(dev, _gpio_direction,
			 (u8 *)&value, 4, 0, 0);
	return status;
}