#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {unsigned int fps; int flags; scalar_t__ start; } ;
typedef  TYPE_1__ AVTimecode ;

/* Variables and functions */
 int AV_TIMECODE_FLAG_DROPFRAME ; 
 int av_timecode_adjust_ntsc_framenum2 (int,unsigned int) ; 

uint32_t av_timecode_get_smpte_from_framenum(const AVTimecode *tc, int framenum)
{
    unsigned fps = tc->fps;
    int drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    int hh, mm, ss, ff;

    framenum += tc->start;
    if (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60) % 60;
    hh = framenum / (fps*3600) % 24;
    return 0         << 31 | // color frame flag (0: unsync mode, 1: sync mode)
           drop      << 30 | // drop  frame flag (0: non drop,    1: drop)
           (ff / 10) << 28 | // tens  of frames
           (ff % 10) << 24 | // units of frames
           0         << 23 | // PC (NTSC) or BGF0 (PAL)
           (ss / 10) << 20 | // tens  of seconds
           (ss % 10) << 16 | // units of seconds
           0         << 15 | // BGF0 (NTSC) or BGF2 (PAL)
           (mm / 10) << 12 | // tens  of minutes
           (mm % 10) <<  8 | // units of minutes
           0         <<  7 | // BGF2 (NTSC) or PC (PAL)
           0         <<  6 | // BGF1
           (hh / 10) <<  4 | // tens  of hours
           (hh % 10);        // units of hours
}