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
 int /*<<< orphan*/  CRT_Device ; 
 int /*<<< orphan*/  DVI_Device ; 
 int /*<<< orphan*/  LCD2_Device ; 
 int /*<<< orphan*/  LCD_Device ; 
 void* STATE_OFF ; 
 void* STATE_ON ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 void* viafb_CRT_ON ; 
 void* viafb_DVI_ON ; 
 void* viafb_LCD2_ON ; 
 void* viafb_LCD_ON ; 
 void* viafb_SAMM_ON ; 
 int /*<<< orphan*/  viafb_active_dev ; 
 int /*<<< orphan*/  viafb_primary_dev ; 

__attribute__((used)) static void parse_active_dev(void)
{
	viafb_CRT_ON = STATE_OFF;
	viafb_DVI_ON = STATE_OFF;
	viafb_LCD_ON = STATE_OFF;
	viafb_LCD2_ON = STATE_OFF;
	/* 1. Modify the active status of devices. */
	/* 2. Keep the order of devices, so we can set corresponding
	   IGA path to devices in SAMM case. */
	/*    Note: The previous of active_dev is primary device,
	   and the following is secondary device. */
	if (!strncmp(viafb_active_dev, "CRT+DVI", 7)) {
		/* CRT+DVI */
		viafb_CRT_ON = STATE_ON;
		viafb_DVI_ON = STATE_ON;
		viafb_primary_dev = CRT_Device;
	} else if (!strncmp(viafb_active_dev, "DVI+CRT", 7)) {
		/* DVI+CRT */
		viafb_CRT_ON = STATE_ON;
		viafb_DVI_ON = STATE_ON;
		viafb_primary_dev = DVI_Device;
	} else if (!strncmp(viafb_active_dev, "CRT+LCD", 7)) {
		/* CRT+LCD */
		viafb_CRT_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = CRT_Device;
	} else if (!strncmp(viafb_active_dev, "LCD+CRT", 7)) {
		/* LCD+CRT */
		viafb_CRT_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	} else if (!strncmp(viafb_active_dev, "DVI+LCD", 7)) {
		/* DVI+LCD */
		viafb_DVI_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = DVI_Device;
	} else if (!strncmp(viafb_active_dev, "LCD+DVI", 7)) {
		/* LCD+DVI */
		viafb_DVI_ON = STATE_ON;
		viafb_LCD_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	} else if (!strncmp(viafb_active_dev, "LCD+LCD2", 8)) {
		viafb_LCD_ON = STATE_ON;
		viafb_LCD2_ON = STATE_ON;
		viafb_primary_dev = LCD_Device;
	} else if (!strncmp(viafb_active_dev, "LCD2+LCD", 8)) {
		viafb_LCD_ON = STATE_ON;
		viafb_LCD2_ON = STATE_ON;
		viafb_primary_dev = LCD2_Device;
	} else if (!strncmp(viafb_active_dev, "CRT", 3)) {
		/* CRT only */
		viafb_CRT_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	} else if (!strncmp(viafb_active_dev, "DVI", 3)) {
		/* DVI only */
		viafb_DVI_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	} else if (!strncmp(viafb_active_dev, "LCD", 3)) {
		/* LCD only */
		viafb_LCD_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	} else {
		viafb_CRT_ON = STATE_ON;
		viafb_SAMM_ON = STATE_OFF;
	}
}