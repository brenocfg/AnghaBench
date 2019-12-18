#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  void* int16_t ;
struct TYPE_13__ {int channels; scalar_t__ sample_fmt; int channel_layout; int debug; } ;
struct TYPE_12__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  AV_CH_LAYOUT_2_1 137 
#define  AV_CH_LAYOUT_2_2 136 
#define  AV_CH_LAYOUT_4POINT0 135 
#define  AV_CH_LAYOUT_5POINT0 134 
#define  AV_CH_LAYOUT_5POINT1 133 
#define  AV_CH_LAYOUT_7POINT0 132 
#define  AV_CH_LAYOUT_7POINT1 131 
#define  AV_CH_LAYOUT_MONO 130 
#define  AV_CH_LAYOUT_STEREO 129 
#define  AV_CH_LAYOUT_SURROUND 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_SAMPLE_FMT_S16 ; 
 int FFALIGN (int,int) ; 
 int FF_DEBUG_BITSTREAM ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 void* bytestream2_get_be16u (int /*<<< orphan*/ *) ; 
 int bytestream2_get_be24u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,int,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int pcm_bluray_parse_header (TYPE_3__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int pcm_bluray_decode_frame(AVCodecContext *avctx, void *data,
                                   int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *src = avpkt->data;
    int buf_size = avpkt->size;
    GetByteContext gb;
    int num_source_channels, channel, retval;
    int sample_size, samples;
    int16_t *dst16;
    int32_t *dst32;

    if (buf_size < 4) {
        av_log(avctx, AV_LOG_ERROR, "PCM packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    if ((retval = pcm_bluray_parse_header(avctx, src)))
        return retval;
    src += 4;
    buf_size -= 4;

    bytestream2_init(&gb, src, buf_size);

    /* There's always an even number of channels in the source */
    num_source_channels = FFALIGN(avctx->channels, 2);
    sample_size = (num_source_channels *
                   (avctx->sample_fmt == AV_SAMPLE_FMT_S16 ? 16 : 24)) >> 3;
    samples = buf_size / sample_size;

    /* get output buffer */
    frame->nb_samples = samples;
    if ((retval = ff_get_buffer(avctx, frame, 0)) < 0)
        return retval;
    dst16 = (int16_t *)frame->data[0];
    dst32 = (int32_t *)frame->data[0];

    if (samples) {
        switch (avctx->channel_layout) {
            /* cases with same number of source and coded channels */
        case AV_CH_LAYOUT_STEREO:
        case AV_CH_LAYOUT_4POINT0:
        case AV_CH_LAYOUT_2_2:
            samples *= num_source_channels;
            if (AV_SAMPLE_FMT_S16 == avctx->sample_fmt) {
#if HAVE_BIGENDIAN
                bytestream2_get_buffer(&gb, dst16, buf_size);
#else
                do {
                    *dst16++ = bytestream2_get_be16u(&gb);
                } while (--samples);
#endif
            } else {
                do {
                    *dst32++ = bytestream2_get_be24u(&gb) << 8;
                } while (--samples);
            }
            break;
        /* cases where number of source channels = coded channels + 1 */
        case AV_CH_LAYOUT_MONO:
        case AV_CH_LAYOUT_SURROUND:
        case AV_CH_LAYOUT_2_1:
        case AV_CH_LAYOUT_5POINT0:
            if (AV_SAMPLE_FMT_S16 == avctx->sample_fmt) {
                do {
#if HAVE_BIGENDIAN
                    bytestream2_get_buffer(&gb, dst16, avctx->channels * 2);
                    dst16 += avctx->channels;
#else
                    channel = avctx->channels;
                    do {
                        *dst16++ = bytestream2_get_be16u(&gb);
                    } while (--channel);
#endif
                    bytestream2_skip(&gb, 2);
                } while (--samples);
            } else {
                do {
                    channel = avctx->channels;
                    do {
                        *dst32++ = bytestream2_get_be24u(&gb) << 8;
                    } while (--channel);
                    bytestream2_skip(&gb, 3);
                } while (--samples);
            }
            break;
            /* remapping: L, R, C, LBack, RBack, LF */
        case AV_CH_LAYOUT_5POINT1:
            if (AV_SAMPLE_FMT_S16 == avctx->sample_fmt) {
                do {
                    dst16[0] = bytestream2_get_be16u(&gb);
                    dst16[1] = bytestream2_get_be16u(&gb);
                    dst16[2] = bytestream2_get_be16u(&gb);
                    dst16[4] = bytestream2_get_be16u(&gb);
                    dst16[5] = bytestream2_get_be16u(&gb);
                    dst16[3] = bytestream2_get_be16u(&gb);
                    dst16 += 6;
                } while (--samples);
            } else {
                do {
                    dst32[0] = bytestream2_get_be24u(&gb) << 8;
                    dst32[1] = bytestream2_get_be24u(&gb) << 8;
                    dst32[2] = bytestream2_get_be24u(&gb) << 8;
                    dst32[4] = bytestream2_get_be24u(&gb) << 8;
                    dst32[5] = bytestream2_get_be24u(&gb) << 8;
                    dst32[3] = bytestream2_get_be24u(&gb) << 8;
                    dst32 += 6;
                } while (--samples);
            }
            break;
            /* remapping: L, R, C, LSide, LBack, RBack, RSide, <unused> */
        case AV_CH_LAYOUT_7POINT0:
            if (AV_SAMPLE_FMT_S16 == avctx->sample_fmt) {
                do {
                    dst16[0] = bytestream2_get_be16u(&gb);
                    dst16[1] = bytestream2_get_be16u(&gb);
                    dst16[2] = bytestream2_get_be16u(&gb);
                    dst16[5] = bytestream2_get_be16u(&gb);
                    dst16[3] = bytestream2_get_be16u(&gb);
                    dst16[4] = bytestream2_get_be16u(&gb);
                    dst16[6] = bytestream2_get_be16u(&gb);
                    dst16 += 7;
                    bytestream2_skip(&gb, 2);
                } while (--samples);
            } else {
                do {
                    dst32[0] = bytestream2_get_be24u(&gb) << 8;
                    dst32[1] = bytestream2_get_be24u(&gb) << 8;
                    dst32[2] = bytestream2_get_be24u(&gb) << 8;
                    dst32[5] = bytestream2_get_be24u(&gb) << 8;
                    dst32[3] = bytestream2_get_be24u(&gb) << 8;
                    dst32[4] = bytestream2_get_be24u(&gb) << 8;
                    dst32[6] = bytestream2_get_be24u(&gb) << 8;
                    dst32 += 7;
                    bytestream2_skip(&gb, 3);
                } while (--samples);
            }
            break;
            /* remapping: L, R, C, LSide, LBack, RBack, RSide, LF */
        case AV_CH_LAYOUT_7POINT1:
            if (AV_SAMPLE_FMT_S16 == avctx->sample_fmt) {
                do {
                    dst16[0] = bytestream2_get_be16u(&gb);
                    dst16[1] = bytestream2_get_be16u(&gb);
                    dst16[2] = bytestream2_get_be16u(&gb);
                    dst16[6] = bytestream2_get_be16u(&gb);
                    dst16[4] = bytestream2_get_be16u(&gb);
                    dst16[5] = bytestream2_get_be16u(&gb);
                    dst16[7] = bytestream2_get_be16u(&gb);
                    dst16[3] = bytestream2_get_be16u(&gb);
                    dst16 += 8;
                } while (--samples);
            } else {
                do {
                    dst32[0] = bytestream2_get_be24u(&gb) << 8;
                    dst32[1] = bytestream2_get_be24u(&gb) << 8;
                    dst32[2] = bytestream2_get_be24u(&gb) << 8;
                    dst32[6] = bytestream2_get_be24u(&gb) << 8;
                    dst32[4] = bytestream2_get_be24u(&gb) << 8;
                    dst32[5] = bytestream2_get_be24u(&gb) << 8;
                    dst32[7] = bytestream2_get_be24u(&gb) << 8;
                    dst32[3] = bytestream2_get_be24u(&gb) << 8;
                    dst32 += 8;
                } while (--samples);
            }
            break;
        }
    }

    *got_frame_ptr = 1;

    retval = bytestream2_tell(&gb);
    if (avctx->debug & FF_DEBUG_BITSTREAM)
        ff_dlog(avctx, "pcm_bluray_decode_frame: decoded %d -> %d bytes\n",
                retval, buf_size);
    return retval + 4;
}