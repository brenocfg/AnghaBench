#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int buf; } ;
struct TYPE_19__ {int block_len_bits; int frame_len_bits; int block_len; double** coefs; TYPE_5__ pb; scalar_t__ ms_stereo; } ;
typedef  TYPE_1__ WMACodecContext ;
struct TYPE_22__ {int block_align; int /*<<< orphan*/  initial_padding; TYPE_1__* priv_data; } ;
struct TYPE_21__ {scalar_t__ pts; } ;
struct TYPE_20__ {int size; scalar_t__ pts; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int MAX_CODED_SUPERFRAME_SIZE ; 
 int apply_window_and_mdct (TYPE_4__*,TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int encode_frame (TYPE_1__*,float**,int /*<<< orphan*/ ,int,int) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_samples_to_time_base (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_5__*) ; 
 int /*<<< orphan*/  put_bits (TYPE_5__*,int,char) ; 
 int put_bits_count (TYPE_5__*) ; 
 int put_bits_ptr (TYPE_5__*) ; 

__attribute__((used)) static int encode_superframe(AVCodecContext *avctx, AVPacket *avpkt,
                             const AVFrame *frame, int *got_packet_ptr)
{
    WMACodecContext *s = avctx->priv_data;
    int i, total_gain, ret, error;

    s->block_len_bits = s->frame_len_bits; // required by non variable block len
    s->block_len      = 1 << s->block_len_bits;

    ret = apply_window_and_mdct(avctx, frame);

    if (ret < 0)
        return ret;

    if (s->ms_stereo) {
        float a, b;
        int i;

        for (i = 0; i < s->block_len; i++) {
            a              = s->coefs[0][i] * 0.5;
            b              = s->coefs[1][i] * 0.5;
            s->coefs[0][i] = a + b;
            s->coefs[1][i] = a - b;
        }
    }

    if ((ret = ff_alloc_packet2(avctx, avpkt, 2 * MAX_CODED_SUPERFRAME_SIZE, 0)) < 0)
        return ret;

    total_gain = 128;
    for (i = 64; i; i >>= 1) {
        error = encode_frame(s, s->coefs, avpkt->data, avpkt->size,
                                 total_gain - i);
        if (error <= 0)
            total_gain -= i;
    }

    while(total_gain <= 128 && error > 0)
        error = encode_frame(s, s->coefs, avpkt->data, avpkt->size, total_gain++);
    if (error > 0) {
        av_log(avctx, AV_LOG_ERROR, "Invalid input data or requested bitrate too low, cannot encode\n");
        avpkt->size = 0;
        return AVERROR(EINVAL);
    }
    av_assert0((put_bits_count(&s->pb) & 7) == 0);
    i= avctx->block_align - (put_bits_count(&s->pb)+7)/8;
    av_assert0(i>=0);
    while(i--)
        put_bits(&s->pb, 8, 'N');

    flush_put_bits(&s->pb);
    av_assert0(put_bits_ptr(&s->pb) - s->pb.buf == avctx->block_align);

    if (frame->pts != AV_NOPTS_VALUE)
        avpkt->pts = frame->pts - ff_samples_to_time_base(avctx, avctx->initial_padding);

    avpkt->size     = avctx->block_align;
    *got_packet_ptr = 1;
    return 0;
}