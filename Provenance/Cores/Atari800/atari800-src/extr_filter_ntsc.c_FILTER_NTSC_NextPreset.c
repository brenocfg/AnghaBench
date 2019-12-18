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
 int FILTER_NTSC_GetPreset () ; 
 int FILTER_NTSC_PRESET_COMPOSITE ; 
 int FILTER_NTSC_PRESET_CUSTOM ; 
 int FILTER_NTSC_PRESET_SIZE ; 
 int /*<<< orphan*/  FILTER_NTSC_SetPreset (int) ; 

void FILTER_NTSC_NextPreset(void)
{
	int preset = FILTER_NTSC_GetPreset();
	
	if (preset == FILTER_NTSC_PRESET_CUSTOM)
		preset = FILTER_NTSC_PRESET_COMPOSITE;
	else
		preset = (preset + 1) % FILTER_NTSC_PRESET_SIZE;
	FILTER_NTSC_SetPreset(preset);
}