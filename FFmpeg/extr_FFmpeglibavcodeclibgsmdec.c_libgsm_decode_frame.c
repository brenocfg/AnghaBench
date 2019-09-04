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
struct TYPE_13__ {int block_align; int frame_size; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ LibGSMDecodeContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  GSM_BLOCK_SIZE ; 
 int GSM_FRAME_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int gsm_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int libgsm_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame_ptr, AVPacket *avpkt)
{
    int i, ret;
    LibGSMDecodeContext *s = avctx->priv_data;
    AVFrame *frame         = data;
    uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    int16_t *samples;

    if (buf_size < avctx->block_align) {
        av_log(avctx, AV_LOG_ERROR, "Packet is too small\n");
        return AVERROR_INVALIDDATA;
    }

    /* get output buffer */
    frame->nb_samples = avctx->frame_size;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples = (int16_t *)frame->data[0];

    for (i = 0; i < avctx->frame_size / GSM_FRAME_SIZE; i++) {
        if ((ret = gsm_decode(s->state, buf, samples)) < 0)
            return -1;
        buf     += GSM_BLOCK_SIZE;
        samples += GSM_FRAME_SIZE;
    }

    *got_frame_ptr = 1;

    return avctx->block_align;
}