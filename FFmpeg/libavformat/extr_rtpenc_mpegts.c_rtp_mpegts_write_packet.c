#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct MuxChain {TYPE_7__* rtp_ctx; TYPE_7__* mpegts_ctx; } ;
struct TYPE_14__ {TYPE_2__** streams; int /*<<< orphan*/ * pb; } ;
struct TYPE_13__ {TYPE_1__** streams; struct MuxChain* priv_data; } ;
struct TYPE_12__ {int size; size_t stream_index; scalar_t__ pts; scalar_t__ dts; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_3__*) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_write_frame (TYPE_7__*,TYPE_3__*) ; 
 int avio_close_dyn_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 

__attribute__((used)) static int rtp_mpegts_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    struct MuxChain *chain = s->priv_data;
    int ret = 0, size;
    uint8_t *buf;
    AVPacket local_pkt;

    if (!chain->mpegts_ctx->pb) {
        if ((ret = avio_open_dyn_buf(&chain->mpegts_ctx->pb)) < 0)
            return ret;
    }
    if ((ret = av_write_frame(chain->mpegts_ctx, pkt)) < 0)
        return ret;
    size = avio_close_dyn_buf(chain->mpegts_ctx->pb, &buf);
    chain->mpegts_ctx->pb = NULL;
    if (size == 0) {
        av_free(buf);
        return 0;
    }
    av_init_packet(&local_pkt);
    local_pkt.data         = buf;
    local_pkt.size         = size;
    local_pkt.stream_index = 0;
    if (pkt->pts != AV_NOPTS_VALUE)
        local_pkt.pts = av_rescale_q(pkt->pts,
                                     s->streams[pkt->stream_index]->time_base,
                                     chain->rtp_ctx->streams[0]->time_base);
    if (pkt->dts != AV_NOPTS_VALUE)
        local_pkt.dts = av_rescale_q(pkt->dts,
                                     s->streams[pkt->stream_index]->time_base,
                                     chain->rtp_ctx->streams[0]->time_base);
    ret = av_write_frame(chain->rtp_ctx, &local_pkt);
    av_free(buf);

    return ret;
}