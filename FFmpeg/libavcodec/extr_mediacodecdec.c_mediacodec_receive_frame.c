#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_21__ {scalar_t__ current_input_buffer; int /*<<< orphan*/  codec; } ;
struct TYPE_20__ {TYPE_1__* priv_data; } ;
struct TYPE_19__ {scalar_t__ size; int data; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {TYPE_6__* ctx; TYPE_2__ buffered_pkt; scalar_t__ amlogic_mpeg2_api23_workaround; scalar_t__ delay_flush; } ;
typedef  TYPE_1__ MediaCodecH264DecContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ ff_AMediaCodec_dequeueInputBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_decode_get_packet (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_mediacodec_dec_flush (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ ff_mediacodec_dec_is_flushing (TYPE_3__*,TYPE_6__*) ; 
 int ff_mediacodec_dec_receive (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 int ff_mediacodec_dec_send (TYPE_3__*,TYPE_6__*,TYPE_2__*,int) ; 

__attribute__((used)) static int mediacodec_receive_frame(AVCodecContext *avctx, AVFrame *frame)
{
    MediaCodecH264DecContext *s = avctx->priv_data;
    int ret;
    ssize_t index;

    /* In delay_flush mode, wait until the user has released or rendered
       all retained frames. */
    if (s->delay_flush && ff_mediacodec_dec_is_flushing(avctx, s->ctx)) {
        if (!ff_mediacodec_dec_flush(avctx, s->ctx)) {
            return AVERROR(EAGAIN);
        }
    }

    /* poll for new frame */
    ret = ff_mediacodec_dec_receive(avctx, s->ctx, frame, false);
    if (ret != AVERROR(EAGAIN))
        return ret;

    /* feed decoder */
    while (1) {
        if (s->ctx->current_input_buffer < 0) {
            /* poll for input space */
            index = ff_AMediaCodec_dequeueInputBuffer(s->ctx->codec, 0);
            if (index < 0) {
                /* no space, block for an output frame to appear */
                return ff_mediacodec_dec_receive(avctx, s->ctx, frame, true);
            }
            s->ctx->current_input_buffer = index;
        }

        /* try to flush any buffered packet data */
        if (s->buffered_pkt.size > 0) {
            ret = ff_mediacodec_dec_send(avctx, s->ctx, &s->buffered_pkt, false);
            if (ret >= 0) {
                s->buffered_pkt.size -= ret;
                s->buffered_pkt.data += ret;
                if (s->buffered_pkt.size <= 0) {
                    av_packet_unref(&s->buffered_pkt);
                } else {
                    av_log(avctx, AV_LOG_WARNING,
                           "could not send entire packet in single input buffer (%d < %d)\n",
                           ret, s->buffered_pkt.size+ret);
                }
            } else if (ret < 0 && ret != AVERROR(EAGAIN)) {
                return ret;
            }

            if (s->amlogic_mpeg2_api23_workaround && s->buffered_pkt.size <= 0) {
                /* fallthrough to fetch next packet regardless of input buffer space */
            } else {
                /* poll for space again */
                continue;
            }
        }

        /* fetch new packet or eof */
        ret = ff_decode_get_packet(avctx, &s->buffered_pkt);
        if (ret == AVERROR_EOF) {
            AVPacket null_pkt = { 0 };
            ret = ff_mediacodec_dec_send(avctx, s->ctx, &null_pkt, true);
            if (ret < 0)
                return ret;
            return ff_mediacodec_dec_receive(avctx, s->ctx, frame, true);
        } else if (ret == AVERROR(EAGAIN) && s->ctx->current_input_buffer < 0) {
            return ff_mediacodec_dec_receive(avctx, s->ctx, frame, true);
        } else if (ret < 0) {
            return ret;
        }
    }

    return AVERROR(EAGAIN);
}