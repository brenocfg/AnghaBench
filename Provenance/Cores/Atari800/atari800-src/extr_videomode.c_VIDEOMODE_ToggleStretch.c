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
 int VIDEOMODE_STRETCH_SIZE ; 
 int VIDEOMODE_SetStretch (int) ; 
 int VIDEOMODE_stretch ; 

int VIDEOMODE_ToggleStretch(void)
{
	return VIDEOMODE_SetStretch((VIDEOMODE_stretch + 1) % VIDEOMODE_STRETCH_SIZE);
}