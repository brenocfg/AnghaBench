#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/ * decoded_bytes_buffer; scalar_t__ scrambled_stream; } ;
struct TYPE_13__ {int block_align; TYPE_4__* priv_data; } ;
struct TYPE_12__ {scalar_t__ extended_data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ ATRAC3Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  SAMPLES_PER_FRAME ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  decode_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int decode_frame (TYPE_3__*,int /*<<< orphan*/  const*,float**) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atrac3_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    ATRAC3Context *q = avctx->priv_data;
    int ret;
    const uint8_t *databuf;

    if (buf_size < avctx->block_align) {
        av_log(avctx, AV_LOG_ERROR,
               "Frame too small (%d bytes). Truncated file?\n", buf_size);
        return AVERROR_INVALIDDATA;
    }

    /* get output buffer */
    frame->nb_samples = SAMPLES_PER_FRAME;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    /* Check if we need to descramble and what buffer to pass on. */
    if (q->scrambled_stream) {
        decode_bytes(buf, q->decoded_bytes_buffer, avctx->block_align);
        databuf = q->decoded_bytes_buffer;
    } else {
        databuf = buf;
    }

    ret = decode_frame(avctx, databuf, (float **)frame->extended_data);
    if (ret) {
        av_log(avctx, AV_LOG_ERROR, "Frame decoding error!\n");
        return ret;
    }

    *got_frame_ptr = 1;

    return avctx->block_align;
}