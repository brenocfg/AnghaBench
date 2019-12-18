#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {scalar_t__ ch_offset; int samples; scalar_t__ block; } ;
typedef  TYPE_1__ WavpackContext ;
struct TYPE_11__ {int bits_per_raw_sample; scalar_t__ channels; int /*<<< orphan*/  sample_fmt; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RL32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLTP ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16P ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32P ; 
 int WV_HEADER_SIZE ; 
 scalar_t__ WV_MAX_SAMPLES ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int wavpack_decode_block (TYPE_3__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wavpack_decode_flush (TYPE_3__*) ; 

__attribute__((used)) static int wavpack_decode_frame(AVCodecContext *avctx, void *data,
                                int *got_frame_ptr, AVPacket *avpkt)
{
    WavpackContext *s  = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    AVFrame *frame     = data;
    int frame_size, ret, frame_flags;

    if (avpkt->size <= WV_HEADER_SIZE)
        return AVERROR_INVALIDDATA;

    s->block     = 0;
    s->ch_offset = 0;

    /* determine number of samples */
    s->samples  = AV_RL32(buf + 20);
    frame_flags = AV_RL32(buf + 24);
    if (s->samples <= 0 || s->samples > WV_MAX_SAMPLES) {
        av_log(avctx, AV_LOG_ERROR, "Invalid number of samples: %d\n",
               s->samples);
        return AVERROR_INVALIDDATA;
    }

    if (frame_flags & 0x80) {
        avctx->sample_fmt = AV_SAMPLE_FMT_FLTP;
    } else if ((frame_flags & 0x03) <= 1) {
        avctx->sample_fmt = AV_SAMPLE_FMT_S16P;
    } else {
        avctx->sample_fmt          = AV_SAMPLE_FMT_S32P;
        avctx->bits_per_raw_sample = ((frame_flags & 0x03) + 1) << 3;
    }

    while (buf_size > 0) {
        if (buf_size <= WV_HEADER_SIZE)
            break;
        frame_size = AV_RL32(buf + 4) - 12;
        buf       += 20;
        buf_size  -= 20;
        if (frame_size <= 0 || frame_size > buf_size) {
            av_log(avctx, AV_LOG_ERROR,
                   "Block %d has invalid size (size %d vs. %d bytes left)\n",
                   s->block, frame_size, buf_size);
            wavpack_decode_flush(avctx);
            return AVERROR_INVALIDDATA;
        }
        if ((ret = wavpack_decode_block(avctx, s->block,
                                        frame, buf, frame_size)) < 0) {
            wavpack_decode_flush(avctx);
            return ret;
        }
        s->block++;
        buf      += frame_size;
        buf_size -= frame_size;
    }

    if (s->ch_offset != avctx->channels) {
        av_log(avctx, AV_LOG_ERROR, "Not enough channels coded in a packet.\n");
        return AVERROR_INVALIDDATA;
    }

    *got_frame_ptr = 1;

    return avpkt->size;
}