#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_12__ {int block_align; int frame_size; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_10__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int /*<<< orphan*/  codec; } ;
typedef  TYPE_1__ LibCodec2Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  codec2_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libcodec2_decode(AVCodecContext *avctx, void *data,
                            int *got_frame_ptr, AVPacket *pkt)
{
    LibCodec2Context *c2 = avctx->priv_data;
    AVFrame *frame = data;
    int ret, nframes, i;
    uint8_t *input;
    int16_t *output;

    nframes           = pkt->size / avctx->block_align;
    frame->nb_samples = avctx->frame_size * nframes;

    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0) {
        return ret;
    }

    input  = pkt->data;
    output = (int16_t *)frame->data[0];

    for (i = 0; i < nframes; i++) {
        codec2_decode(c2->codec, output, input);
        input  += avctx->block_align;
        output += avctx->frame_size;
    }

    *got_frame_ptr = nframes > 0;
    return nframes * avctx->block_align;
}