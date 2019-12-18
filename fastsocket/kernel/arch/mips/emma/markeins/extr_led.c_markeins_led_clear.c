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
 scalar_t__ LED_BASE ; 
 int /*<<< orphan*/  clear ; 
 int /*<<< orphan*/  emma2rh_out32 (scalar_t__,int /*<<< orphan*/ ) ; 

void markeins_led_clear(void)
{
	emma2rh_out32(LED_BASE, clear);
	emma2rh_out32(LED_BASE + 4, clear);
}