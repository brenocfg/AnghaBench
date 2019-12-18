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
typedef  scalar_t__ VIDEOMODE_MODE_t ;

/* Variables and functions */
 scalar_t__ CurrentDisplayMode () ; 
 int /*<<< orphan*/  VIDEOMODE_Update () ; 
 int force_standard_screen ; 

void VIDEOMODE_ForceStandardScreen(int value)
{
	VIDEOMODE_MODE_t prev_mode = CurrentDisplayMode();
	force_standard_screen = value;
	if (prev_mode != CurrentDisplayMode())
		VIDEOMODE_Update();
}