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
struct TYPE_3__ {int fps; int flags; scalar_t__ start; } ;
typedef  TYPE_1__ AVTimecode ;

/* Variables and functions */
 int AV_TIMECODE_FLAG_24HOURSMAX ; 
 int AV_TIMECODE_FLAG_ALLOWNEGATIVE ; 
 int AV_TIMECODE_FLAG_DROPFRAME ; 
 int /*<<< orphan*/  AV_TIMECODE_STR_SIZE ; 
 int av_timecode_adjust_ntsc_framenum2 (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,char,int) ; 

char *av_timecode_make_string(const AVTimecode *tc, char *buf, int framenum)
{
    int fps = tc->fps;
    int drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    int hh, mm, ss, ff, neg = 0;

    framenum += tc->start;
    if (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    if (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60)   % 60;
    hh = framenum / (fps*3600);
    if (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%02d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff);
    return buf;
}