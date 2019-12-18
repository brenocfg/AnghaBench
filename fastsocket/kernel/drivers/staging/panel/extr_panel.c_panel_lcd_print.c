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
 scalar_t__ lcd_enabled ; 
 scalar_t__ lcd_initialized ; 
 int /*<<< orphan*/  lcd_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void panel_lcd_print(char *s)
{
	if (lcd_enabled && lcd_initialized)
		lcd_write(NULL, s, strlen(s), NULL);
}