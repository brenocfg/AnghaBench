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
struct TYPE_3__ {int /*<<< orphan*/  avg_frame_rate; } ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static AVRational find_fps(AVFormatContext *s, AVStream *st)
{
    AVRational rate = st->avg_frame_rate;

#if FF_API_LAVF_AVCTX
    FF_DISABLE_DEPRECATION_WARNINGS
    rate = av_inv_q(st->codec->time_base);
    if (av_timecode_check_frame_rate(rate) < 0) {
        av_log(s, AV_LOG_DEBUG, "timecode: tbc=%d/%d invalid, fallback on %d/%d\n",
               rate.num, rate.den, st->avg_frame_rate.num, st->avg_frame_rate.den);
        rate = st->avg_frame_rate;
    }
    FF_ENABLE_DEPRECATION_WARNINGS
#endif

    return rate;
}