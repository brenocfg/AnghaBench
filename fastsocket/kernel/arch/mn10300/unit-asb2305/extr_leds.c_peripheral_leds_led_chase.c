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
 int /*<<< orphan*/  ASB2305_7SEGLEDS ; 
 size_t asb2305_led_chase ; 
 int /*<<< orphan*/ * asb2305_led_chase_tbl ; 

void peripheral_leds_led_chase(void)
{
	ASB2305_7SEGLEDS = asb2305_led_chase_tbl[asb2305_led_chase];
	asb2305_led_chase++;
	if (asb2305_led_chase >= 6)
		asb2305_led_chase = 0;
}