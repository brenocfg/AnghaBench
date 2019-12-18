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
 int /*<<< orphan*/  ASB2303_7SEGLEDS ; 
 int ASB2303_GPIO0DEF ; 
 size_t asb2303_led_chase ; 
 int /*<<< orphan*/ * asb2303_led_chase_tbl ; 

void peripheral_leds_led_chase(void)
{
	ASB2303_GPIO0DEF = 0x5555;	/* configure as an output port */
	ASB2303_7SEGLEDS = asb2303_led_chase_tbl[asb2303_led_chase];
	asb2303_led_chase++;
	if (asb2303_led_chase >= 6)
		asb2303_led_chase = 0;
}