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
typedef  enum exception_code { ____Placeholder_exception_code } exception_code ;

/* Variables and functions */
 int ASB2305_7SEGLEDS ; 
 int* asb2305_led_hex_tbl ; 

void peripheral_leds_display_exception(enum exception_code code)
{
	u32 leds;

	leds = asb2305_led_hex_tbl[(code/0x100) % 0x10];
	leds <<= 8;
	leds |= asb2305_led_hex_tbl[(code/0x10) % 0x10];
	leds <<= 8;
	leds |= asb2305_led_hex_tbl[code % 0x10];
	leds |= 0x6d010101;

	ASB2305_7SEGLEDS = leds;
}