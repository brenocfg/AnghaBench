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

int av_timecode_adjust_ntsc_framenum2(int framenum, int fps)
{
    /* only works for NTSC 29.97 and 59.94 */
    int drop_frames = 0;
    int d, m, frames_per_10mins;

    if (fps == 30) {
        drop_frames = 2;
        frames_per_10mins = 17982;
    } else if (fps == 60) {
        drop_frames = 4;
        frames_per_10mins = 35964;
    } else
        return framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    return framenum + 9 * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}