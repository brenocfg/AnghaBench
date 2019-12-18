#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int member_1; int revents; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {TYPE_2__* priv_data; } ;
struct TYPE_16__ {size_t stream_index; } ;
struct TYPE_15__ {scalar_t__ state; size_t nb_rtsp_streams; scalar_t__ lower_transport; TYPE_1__** rtsp_streams; int /*<<< orphan*/  rtsp_hd; } ;
struct TYPE_14__ {TYPE_4__* transport_priv; } ;
typedef  TYPE_1__ RTSPStream ;
typedef  TYPE_2__ RTSPState ;
typedef  int /*<<< orphan*/  RTSPMessageHeader ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  EPIPE ; 
 int POLLIN ; 
 scalar_t__ RTSP_LOWER_TRANSPORT_TCP ; 
 scalar_t__ RTSP_STATE_STREAMING ; 
 int ff_rtsp_read_reply (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_rtsp_skip_packet (TYPE_4__*) ; 
 int ff_rtsp_tcp_write_packet (TYPE_4__*,TYPE_1__*) ; 
 int ff_write_chained (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_get_file_handle (int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtsp_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    RTSPState *rt = s->priv_data;
    RTSPStream *rtsp_st;
    int n;
    struct pollfd p = {ffurl_get_file_handle(rt->rtsp_hd), POLLIN, 0};
    AVFormatContext *rtpctx;
    int ret;

    while (1) {
        n = poll(&p, 1, 0);
        if (n <= 0)
            break;
        if (p.revents & POLLIN) {
            RTSPMessageHeader reply;

            /* Don't let ff_rtsp_read_reply handle interleaved packets,
             * since it would block and wait for an RTSP reply on the socket
             * (which may not be coming any time soon) if it handles
             * interleaved packets internally. */
            ret = ff_rtsp_read_reply(s, &reply, NULL, 1, NULL);
            if (ret < 0)
                return AVERROR(EPIPE);
            if (ret == 1)
                ff_rtsp_skip_packet(s);
            /* XXX: parse message */
            if (rt->state != RTSP_STATE_STREAMING)
                return AVERROR(EPIPE);
        }
    }

    if (pkt->stream_index < 0 || pkt->stream_index >= rt->nb_rtsp_streams)
        return AVERROR_INVALIDDATA;
    rtsp_st = rt->rtsp_streams[pkt->stream_index];
    rtpctx = rtsp_st->transport_priv;

    ret = ff_write_chained(rtpctx, 0, pkt, s, 0);
    /* ff_write_chained does all the RTP packetization. If using TCP as
     * transport, rtpctx->pb is only a dyn_packet_buf that queues up the
     * packets, so we need to send them out on the TCP connection separately.
     */
    if (!ret && rt->lower_transport == RTSP_LOWER_TRANSPORT_TCP)
        ret = ff_rtsp_tcp_write_packet(s, rtsp_st);
    return ret;
}