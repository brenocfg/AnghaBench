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
 int /*<<< orphan*/  viafb_crt_disable () ; 
 int /*<<< orphan*/  viafb_dvi_disable () ; 
 int /*<<< orphan*/  viafb_lcd_disable () ; 

__attribute__((used)) static void device_off(void)
{
	viafb_crt_disable();
	viafb_dvi_disable();
	viafb_lcd_disable();
}