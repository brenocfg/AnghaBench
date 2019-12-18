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
 int FCEUI_GetDesiredFPS () ; 
 int desiredfps ; 
 int fps_scale ; 
 int tfreq ; 

void RefreshThrottleFPS(void)
{
       desiredfps=FCEUI_GetDesiredFPS()>>8;
       desiredfps=(desiredfps*fps_scale)>>8;
       tfreq=10000000;
       tfreq<<=16;    /* Adjustment for fps returned from FCEUI_GetDesiredFPS(). */
}