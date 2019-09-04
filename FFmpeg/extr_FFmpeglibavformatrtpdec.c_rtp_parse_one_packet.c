#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int int16_t ;
struct TYPE_12__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_11__ {scalar_t__ prev_ret; scalar_t__ seq; int queue_size; int queue_len; int /*<<< orphan*/  ic; int /*<<< orphan*/  queue; int /*<<< orphan*/  statistics; TYPE_3__* st; int /*<<< orphan*/  dynamic_protocol_context; TYPE_1__* handler; } ;
struct TYPE_10__ {int (* parse_packet ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ RTPDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RB16 (int*) ; 
 int /*<<< orphan*/  AV_RB32 (int*) ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  RTP_NOTS_VALUE ; 
 scalar_t__ RTP_PT_IS_RTCP (int) ; 
 int RTP_VERSION ; 
 int /*<<< orphan*/  av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int enqueue_packet (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  finalize_packet (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtcp_parse_packet (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  rtcp_update_jitter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtp_parse_packet_internal (TYPE_2__*,int /*<<< orphan*/ *,int*,int) ; 
 int rtp_parse_queued_packet (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtp_parse_one_packet(RTPDemuxContext *s, AVPacket *pkt,
                                uint8_t **bufptr, int len)
{
    uint8_t *buf = bufptr ? *bufptr : NULL;
    int flags = 0;
    uint32_t timestamp;
    int rv = 0;

    if (!buf) {
        /* If parsing of the previous packet actually returned 0 or an error,
         * there's nothing more to be parsed from that packet, but we may have
         * indicated that we can return the next enqueued packet. */
        if (s->prev_ret <= 0)
            return rtp_parse_queued_packet(s, pkt);
        /* return the next packets, if any */
        if (s->handler && s->handler->parse_packet) {
            /* timestamp should be overwritten by parse_packet, if not,
             * the packet is left with pts == AV_NOPTS_VALUE */
            timestamp = RTP_NOTS_VALUE;
            rv        = s->handler->parse_packet(s->ic, s->dynamic_protocol_context,
                                                 s->st, pkt, &timestamp, NULL, 0, 0,
                                                 flags);
            finalize_packet(s, pkt, timestamp);
            return rv;
        }
    }

    if (len < 12)
        return -1;

    if ((buf[0] & 0xc0) != (RTP_VERSION << 6))
        return -1;
    if (RTP_PT_IS_RTCP(buf[1])) {
        return rtcp_parse_packet(s, buf, len);
    }

    if (s->st) {
        int64_t received = av_gettime_relative();
        uint32_t arrival_ts = av_rescale_q(received, AV_TIME_BASE_Q,
                                           s->st->time_base);
        timestamp = AV_RB32(buf + 4);
        // Calculate the jitter immediately, before queueing the packet
        // into the reordering queue.
        rtcp_update_jitter(&s->statistics, timestamp, arrival_ts);
    }

    if ((s->seq == 0 && !s->queue) || s->queue_size <= 1) {
        /* First packet, or no reordering */
        return rtp_parse_packet_internal(s, pkt, buf, len);
    } else {
        uint16_t seq = AV_RB16(buf + 2);
        int16_t diff = seq - s->seq;
        if (diff < 0) {
            /* Packet older than the previously emitted one, drop */
            av_log(s->ic, AV_LOG_WARNING,
                   "RTP: dropping old packet received too late\n");
            return -1;
        } else if (diff <= 1) {
            /* Correct packet */
            rv = rtp_parse_packet_internal(s, pkt, buf, len);
            return rv;
        } else {
            /* Still missing some packet, enqueue this one. */
            rv = enqueue_packet(s, buf, len);
            if (rv < 0)
                return rv;
            *bufptr = NULL;
            /* Return the first enqueued packet if the queue is full,
             * even if we're missing something */
            if (s->queue_len >= s->queue_size) {
                av_log(s->ic, AV_LOG_WARNING, "jitter buffer full\n");
                return rtp_parse_queued_packet(s, pkt);
            }
            return -1;
        }
    }
}