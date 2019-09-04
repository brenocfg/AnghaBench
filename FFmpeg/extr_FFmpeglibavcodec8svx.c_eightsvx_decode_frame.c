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
struct TYPE_13__ {int channels; scalar_t__ frame_number; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int nb_samples; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int size; scalar_t__* data; } ;
struct TYPE_10__ {size_t data_idx; int data_size; int /*<<< orphan*/  table; scalar_t__* fib_acc; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ EightSvxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 void* av_malloc (int) ; 
 int /*<<< orphan*/  delta_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 

__attribute__((used)) static int eightsvx_decode_frame(AVCodecContext *avctx, void *data,
                                 int *got_frame_ptr, AVPacket *avpkt)
{
    EightSvxContext *esc = avctx->priv_data;
    AVFrame *frame       = data;
    int buf_size;
    int ch, ret;
    int hdr_size = 2;

    /* decode and interleave the first packet */
    if (!esc->data[0] && avpkt) {
        int chan_size = avpkt->size / avctx->channels - hdr_size;

        if (avpkt->size % avctx->channels) {
            av_log(avctx, AV_LOG_WARNING, "Packet with odd size, ignoring last byte\n");
        }
        if (avpkt->size < (hdr_size + 1) * avctx->channels) {
            av_log(avctx, AV_LOG_ERROR, "packet size is too small\n");
            return AVERROR_INVALIDDATA;
        }

        esc->fib_acc[0] = avpkt->data[1] + 128;
        if (avctx->channels == 2)
            esc->fib_acc[1] = avpkt->data[2+chan_size+1] + 128;

        esc->data_idx  = 0;
        esc->data_size = chan_size;
        if (!(esc->data[0] = av_malloc(chan_size)))
            return AVERROR(ENOMEM);
        if (avctx->channels == 2) {
            if (!(esc->data[1] = av_malloc(chan_size))) {
                av_freep(&esc->data[0]);
                return AVERROR(ENOMEM);
            }
        }
        memcpy(esc->data[0], &avpkt->data[hdr_size], chan_size);
        if (avctx->channels == 2)
            memcpy(esc->data[1], &avpkt->data[2*hdr_size+chan_size], chan_size);
    }
    if (!esc->data[0]) {
        av_log(avctx, AV_LOG_ERROR, "unexpected empty packet\n");
        return AVERROR_INVALIDDATA;
    }

    /* decode next piece of data from the buffer */
    buf_size = FFMIN(MAX_FRAME_SIZE, esc->data_size - esc->data_idx);
    if (buf_size <= 0) {
        *got_frame_ptr = 0;
        return avpkt->size;
    }

    /* get output buffer */
    frame->nb_samples = buf_size * 2;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    for (ch = 0; ch < avctx->channels; ch++) {
        delta_decode(frame->data[ch], &esc->data[ch][esc->data_idx],
                     buf_size, &esc->fib_acc[ch], esc->table);
    }

    esc->data_idx += buf_size;

    *got_frame_ptr = 1;

    return ((avctx->frame_number == 0)*hdr_size + buf_size)*avctx->channels;
}