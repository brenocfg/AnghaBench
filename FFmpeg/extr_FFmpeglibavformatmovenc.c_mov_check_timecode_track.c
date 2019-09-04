#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * streams; } ;
typedef  int /*<<< orphan*/  AVTimecode ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int av_timecode_init_from_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  find_fps (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_check_timecode_track(AVFormatContext *s, AVTimecode *tc, int src_index, const char *tcstr)
{
    int ret;

    /* compute the frame number */
    ret = av_timecode_init_from_string(tc, find_fps(s,  s->streams[src_index]), tcstr, s);
    return ret;
}