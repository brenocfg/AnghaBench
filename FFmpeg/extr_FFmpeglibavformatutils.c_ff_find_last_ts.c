#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pos_max ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_read_timestamp (TYPE_1__*,int,scalar_t__*,scalar_t__,scalar_t__ (*) (struct AVFormatContext*,int,scalar_t__*,scalar_t__)) ; 

int ff_find_last_ts(AVFormatContext *s, int stream_index, int64_t *ts, int64_t *pos,
                    int64_t (*read_timestamp)(struct AVFormatContext *, int , int64_t *, int64_t ))
{
    int64_t step = 1024;
    int64_t limit, ts_max;
    int64_t filesize = avio_size(s->pb);
    int64_t pos_max  = filesize - 1;
    do {
        limit = pos_max;
        pos_max = FFMAX(0, (pos_max) - step);
        ts_max  = ff_read_timestamp(s, stream_index,
                                    &pos_max, limit, read_timestamp);
        step   += step;
    } while (ts_max == AV_NOPTS_VALUE && 2*limit > step);
    if (ts_max == AV_NOPTS_VALUE)
        return -1;

    for (;;) {
        int64_t tmp_pos = pos_max + 1;
        int64_t tmp_ts  = ff_read_timestamp(s, stream_index,
                                            &tmp_pos, INT64_MAX, read_timestamp);
        if (tmp_ts == AV_NOPTS_VALUE)
            break;
        av_assert0(tmp_pos > pos_max);
        ts_max  = tmp_ts;
        pos_max = tmp_pos;
        if (tmp_pos >= filesize)
            break;
    }

    if (ts)
        *ts = ts_max;
    if (pos)
        *pos = pos_max;

    return 0;
}