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
 int /*<<< orphan*/  lcd_rate_defaults ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  set_reg_setting (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unset_lcd_custom_rate_(void)
{
	printf("reset to prev LCD refresh.\n");
	set_reg_setting(lcd_rate_defaults);
}