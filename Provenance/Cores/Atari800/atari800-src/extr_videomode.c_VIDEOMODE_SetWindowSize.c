#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int width; unsigned int height; } ;

/* Variables and functions */
 int TRUE ; 
 int UpdateVideoWindowed (int) ; 
 scalar_t__ VIDEOMODE_windowed ; 
 scalar_t__ force_windowed ; 
 TYPE_1__ window_resolution ; 

int VIDEOMODE_SetWindowSize(unsigned int width, unsigned int height)
{
	window_resolution.width = width;
	window_resolution.height = height;
	if (VIDEOMODE_windowed || force_windowed)
		return UpdateVideoWindowed(TRUE);
	return TRUE;
}