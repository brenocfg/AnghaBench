#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {int channels; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  sample_fmt; TYPE_1__* priv_data; } ;
struct TYPE_12__ {scalar_t__* data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int pktsize; int /*<<< orphan*/  dec_state; int /*<<< orphan*/  stereo; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  bits; } ;
typedef  TYPE_1__ LibSpeexContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  SPEEX_GET_BITRATE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int speex_bits_peek_unsigned (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  speex_bits_read_from (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int speex_bits_remaining (int /*<<< orphan*/ *) ; 
 int speex_decode_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_decode_stereo_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_decoder_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int libspeex_decode_frame(AVCodecContext *avctx, void *data,
                                 int *got_frame_ptr, AVPacket *avpkt)
{
    uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    LibSpeexContext *s = avctx->priv_data;
    AVFrame *frame     = data;
    int16_t *output;
    int ret, consumed = 0;
    avctx->sample_fmt = AV_SAMPLE_FMT_S16;

    /* get output buffer */
    frame->nb_samples = s->frame_size;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    output = (int16_t *)frame->data[0];

    /* if there is not enough data left for the smallest possible frame or the
       next 5 bits are a terminator code, reset the libspeex buffer using the
       current packet, otherwise ignore the current packet and keep decoding
       frames from the libspeex buffer. */
    if (speex_bits_remaining(&s->bits) < 5 ||
        speex_bits_peek_unsigned(&s->bits, 5) == 0xF) {
        /* check for flush packet */
        if (!buf || !buf_size) {
            *got_frame_ptr = 0;
            return buf_size;
        }
        if (s->pktsize && buf_size == 62)
            buf_size = s->pktsize;
        /* set new buffer */
        speex_bits_read_from(&s->bits, buf, buf_size);
        consumed = avpkt->size;
    }

    /* decode a single frame */
    ret = speex_decode_int(s->dec_state, &s->bits, output);
    if (ret <= -2) {
        av_log(avctx, AV_LOG_ERROR, "Error decoding Speex frame.\n");
        return AVERROR_INVALIDDATA;
    }
    if (avctx->channels == 2)
        speex_decode_stereo_int(output, s->frame_size, &s->stereo);

    *got_frame_ptr = 1;

    if (!avctx->bit_rate)
        speex_decoder_ctl(s->dec_state, SPEEX_GET_BITRATE, &avctx->bit_rate);
    return consumed;
}