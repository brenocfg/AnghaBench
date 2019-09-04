#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__** streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  cur_dts; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbg_read_seek2(AVFormatContext *avf, int stream_index,
                          int64_t min_ts, int64_t ts, int64_t max_ts, int flags)
{
    if (flags || stream_index > 0)
        return AVERROR(EINVAL);
    if (stream_index < 0)
        ts = av_rescale_q(ts, AV_TIME_BASE_Q, avf->streams[0]->time_base);
    avf->streams[0]->cur_dts = ts;
    return 0;
}