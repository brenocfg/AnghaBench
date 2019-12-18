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
 int /*<<< orphan*/  FALSE ; 
 int UpdateVideoFullscreen () ; 
 int UpdateVideoWindowed (int /*<<< orphan*/ ) ; 
 scalar_t__ VIDEOMODE_windowed ; 
 scalar_t__ force_windowed ; 

int VIDEOMODE_Update(void)
{
	if (VIDEOMODE_windowed || force_windowed)
		return UpdateVideoWindowed(FALSE);
	else
		return UpdateVideoFullscreen();
}