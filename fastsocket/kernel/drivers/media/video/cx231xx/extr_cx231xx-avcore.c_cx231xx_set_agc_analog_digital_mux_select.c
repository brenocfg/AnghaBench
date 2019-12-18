#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  agc_analog_digital_select_gpio; } ;
struct cx231xx {TYPE_1__ board; } ;

/* Variables and functions */
 int cx231xx_set_gpio_direction (struct cx231xx*,int /*<<< orphan*/ ,int) ; 
 int cx231xx_set_gpio_value (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx231xx_set_agc_analog_digital_mux_select(struct cx231xx *dev,
					      u8 analog_or_digital)
{
	int status = 0;

	/* first set the direction to output */
	status = cx231xx_set_gpio_direction(dev,
					    dev->board.
					    agc_analog_digital_select_gpio, 1);

	/* 0 - demod ; 1 - Analog mode */
	status = cx231xx_set_gpio_value(dev,
				   dev->board.agc_analog_digital_select_gpio,
				   analog_or_digital);

	return status;
}