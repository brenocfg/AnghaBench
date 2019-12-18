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
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */
 int check_fps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fps_from_frame_rate (int /*<<< orphan*/ ) ; 

int av_timecode_check_frame_rate(AVRational rate)
{
    return check_fps(fps_from_frame_rate(rate));
}