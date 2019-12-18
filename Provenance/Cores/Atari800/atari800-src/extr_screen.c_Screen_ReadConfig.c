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
 int FALSE ; 
 int Screen_show_1200_leds ; 
 int Screen_show_atari_speed ; 
 int Screen_show_disk_led ; 
 int Screen_show_sector_counter ; 
 int TRUE ; 
 int Util_sscanbool (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int Screen_ReadConfig(char *string, char *ptr)
{
	if (strcmp(string, "SCREEN_SHOW_SPEED") == 0)
		return (Screen_show_atari_speed = Util_sscanbool(ptr)) != -1;
	else if (strcmp(string, "SCREEN_SHOW_IO_ACTIVITY") == 0)
		return (Screen_show_disk_led = Util_sscanbool(ptr)) != -1;
	else if (strcmp(string, "SCREEN_SHOW_IO_COUNTER") == 0)
		return (Screen_show_sector_counter = Util_sscanbool(ptr)) != -1;
	else if (strcmp(string, "SCREEN_SHOW_1200XL_LEDS") == 0)
		return (Screen_show_1200_leds = Util_sscanbool(ptr)) != -1;
	else return FALSE;
	return TRUE;
}