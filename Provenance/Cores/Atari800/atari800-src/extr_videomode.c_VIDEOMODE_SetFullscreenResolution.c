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
 int TRUE ; 
 int UpdateVideoFullscreen () ; 
 int /*<<< orphan*/  VIDEOMODE_windowed ; 
 unsigned int current_resolution ; 
 int /*<<< orphan*/  force_windowed ; 

int VIDEOMODE_SetFullscreenResolution(unsigned int res_id)
{
	current_resolution = res_id;
	if (!VIDEOMODE_windowed && !force_windowed)
		return UpdateVideoFullscreen();
	return TRUE;
}