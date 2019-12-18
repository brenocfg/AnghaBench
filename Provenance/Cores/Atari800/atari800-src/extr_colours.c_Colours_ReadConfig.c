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
 scalar_t__ COLOURS_NTSC_ReadConfig (char*,char*) ; 
 scalar_t__ COLOURS_PAL_ReadConfig (char*,char*) ; 
 int FALSE ; 
 int TRUE ; 

int Colours_ReadConfig(char *option, char *ptr)
{
	if (COLOURS_NTSC_ReadConfig(option, ptr)) {
	}
	else if (COLOURS_PAL_ReadConfig(option, ptr)) {
	}
	else return FALSE; /* no match */
	return TRUE; /* matched something */
}