#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int debug; TYPE_2__* pb; TYPE_3__** streams; TYPE_1__* oformat; } ;
struct TYPE_27__ {size_t stream_index; scalar_t__ dts; scalar_t__ pts; int /*<<< orphan*/  size; } ;
struct TYPE_26__ {int /*<<< orphan*/  nb_frames; } ;
struct TYPE_25__ {int error; } ;
struct TYPE_24__ {int flags; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVFMT_NOTIMESTAMPS ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_FDEBUG_TS ; 
 int /*<<< orphan*/  av_init_packet (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 
 int /*<<< orphan*/  av_ts2str (scalar_t__) ; 
 int compute_muxer_pkt_fields (TYPE_5__*,TYPE_3__*,TYPE_4__*) ; 
 int do_packet_auto_bsf (TYPE_5__*,TYPE_4__*) ; 
 int interleave_packet (TYPE_5__*,TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int prepare_input_packet (TYPE_5__*,TYPE_4__*) ; 
 int write_packet (TYPE_5__*,TYPE_4__*) ; 

int av_interleaved_write_frame(AVFormatContext *s, AVPacket *pkt)
{
    int ret, flush = 0;

    ret = prepare_input_packet(s, pkt);
    if (ret < 0)
        goto fail;

    if (pkt) {
        AVStream *st = s->streams[pkt->stream_index];

        ret = do_packet_auto_bsf(s, pkt);
        if (ret == 0)
            return 0;
        else if (ret < 0)
            goto fail;

        if (s->debug & FF_FDEBUG_TS)
            av_log(s, AV_LOG_DEBUG, "av_interleaved_write_frame size:%d dts:%s pts:%s\n",
                pkt->size, av_ts2str(pkt->dts), av_ts2str(pkt->pts));

#if FF_API_COMPUTE_PKT_FIELDS2 && FF_API_LAVF_AVCTX
        if ((ret = compute_muxer_pkt_fields(s, st, pkt)) < 0 && !(s->oformat->flags & AVFMT_NOTIMESTAMPS))
            goto fail;
#endif

        if (pkt->dts == AV_NOPTS_VALUE && !(s->oformat->flags & AVFMT_NOTIMESTAMPS)) {
            ret = AVERROR(EINVAL);
            goto fail;
        }
    } else {
        av_log(s, AV_LOG_TRACE, "av_interleaved_write_frame FLUSH\n");
        flush = 1;
    }

    for (;; ) {
        AVPacket opkt;
        int ret = interleave_packet(s, &opkt, pkt, flush);
        if (pkt) {
            memset(pkt, 0, sizeof(*pkt));
            av_init_packet(pkt);
            pkt = NULL;
        }
        if (ret <= 0) //FIXME cleanup needed for ret<0 ?
            return ret;

        ret = write_packet(s, &opkt);
        if (ret >= 0)
            s->streams[opkt.stream_index]->nb_frames++;

        av_packet_unref(&opkt);

        if (ret < 0)
            return ret;
        if(s->pb && s->pb->error)
            return s->pb->error;
    }
fail:
    av_packet_unref(pkt);
    return ret;
}