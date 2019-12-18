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
 int hb_video_rate_clock ; 
 int hb_video_rate_max ; 
 int hb_video_rate_min ; 

void hb_video_framerate_get_limits(int *low, int *high, int *clock)
{
    *low   = hb_video_rate_min;
    *high  = hb_video_rate_max;
    *clock = hb_video_rate_clock;
}