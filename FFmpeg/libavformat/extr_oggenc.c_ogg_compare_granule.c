#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {TYPE_2__** streams; } ;
struct TYPE_8__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  priv_data; } ;
struct TYPE_7__ {size_t stream_index; int granule; } ;
typedef  TYPE_1__ OGGPage ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ogg_granule_to_timestamp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ogg_compare_granule(AVFormatContext *s, OGGPage *next, OGGPage *page)
{
    AVStream *st2 = s->streams[next->stream_index];
    AVStream *st  = s->streams[page->stream_index];
    int64_t next_granule, cur_granule;

    if (next->granule == -1 || page->granule == -1)
        return 0;

    next_granule = av_rescale_q(ogg_granule_to_timestamp(st2->priv_data, next->granule),
                                st2->time_base, AV_TIME_BASE_Q);
    cur_granule  = av_rescale_q(ogg_granule_to_timestamp(st->priv_data, page->granule),
                                st ->time_base, AV_TIME_BASE_Q);
    return next_granule > cur_granule;
}