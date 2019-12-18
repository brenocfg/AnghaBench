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
struct TYPE_2__ {scalar_t__ regbase; } ;

/* Variables and functions */
 scalar_t__ GPIOILEVEL ; 
 TYPE_1__* rb532_gpio_chip ; 
 int /*<<< orphan*/  rb532_set_bit (int,unsigned int,scalar_t__) ; 

void rb532_gpio_set_ilevel(int bit, unsigned gpio)
{
	rb532_set_bit(bit, gpio, rb532_gpio_chip->regbase + GPIOILEVEL);
}