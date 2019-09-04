#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {scalar_t__ pts; scalar_t__ dts; } ;
struct TYPE_11__ {scalar_t__ last_rtcp_ntp_time; scalar_t__ last_rtcp_timestamp; scalar_t__ first_rtcp_ntp_time; scalar_t__ range_start_offset; scalar_t__ rtcp_ts_offset; scalar_t__ base_timestamp; scalar_t__ timestamp; scalar_t__ unwrapped_timestamp; TYPE_3__* st; TYPE_1__* ic; } ;
struct TYPE_9__ {scalar_t__ num; int /*<<< orphan*/  den; } ;
struct TYPE_10__ {TYPE_2__ time_base; } ;
struct TYPE_8__ {int nb_streams; } ;
typedef  TYPE_4__ RTPDemuxContext ;
typedef  TYPE_5__ AVPacket ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ RTP_NOTS_VALUE ; 
 scalar_t__ av_rescale (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void finalize_packet(RTPDemuxContext *s, AVPacket *pkt, uint32_t timestamp)
{
    if (pkt->pts != AV_NOPTS_VALUE || pkt->dts != AV_NOPTS_VALUE)
        return; /* Timestamp already set by depacketizer */
    if (timestamp == RTP_NOTS_VALUE)
        return;

    if (s->last_rtcp_ntp_time != AV_NOPTS_VALUE && s->ic->nb_streams > 1) {
        int64_t addend;
        int delta_timestamp;

        /* compute pts from timestamp with received ntp_time */
        delta_timestamp = timestamp - s->last_rtcp_timestamp;
        /* convert to the PTS timebase */
        addend = av_rescale(s->last_rtcp_ntp_time - s->first_rtcp_ntp_time,
                            s->st->time_base.den,
                            (uint64_t) s->st->time_base.num << 32);
        pkt->pts = s->range_start_offset + s->rtcp_ts_offset + addend +
                   delta_timestamp;
        return;
    }

    if (!s->base_timestamp)
        s->base_timestamp = timestamp;
    /* assume that the difference is INT32_MIN < x < INT32_MAX,
     * but allow the first timestamp to exceed INT32_MAX */
    if (!s->timestamp)
        s->unwrapped_timestamp += timestamp;
    else
        s->unwrapped_timestamp += (int32_t)(timestamp - s->timestamp);
    s->timestamp = timestamp;
    pkt->pts     = s->unwrapped_timestamp + s->range_start_offset -
                   s->base_timestamp;
}