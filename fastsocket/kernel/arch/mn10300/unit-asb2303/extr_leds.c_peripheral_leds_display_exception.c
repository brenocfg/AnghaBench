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
typedef  enum exception_code { ____Placeholder_exception_code } exception_code ;

/* Variables and functions */
 int ASB2303_7SEGLEDS ; 
 int ASB2303_GPIO0DEF ; 

void peripheral_leds_display_exception(enum exception_code code)
{
	ASB2303_GPIO0DEF = 0x5555;	/* configure as an output port */
	ASB2303_7SEGLEDS = 0x6d;	/* triple horizontal bar */
}