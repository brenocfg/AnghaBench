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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_14__ {TYPE_1__* priv_data; } ;
struct TYPE_13__ {scalar_t__* data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_12__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {scalar_t__ checksum_size; int /*<<< orphan*/  cur_tone; int /*<<< orphan*/  nb_tones; int /*<<< orphan*/  frame_size; TYPE_4__* avctx; } ;
typedef  TYPE_1__ QDMCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int decode_frame (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qdmc_flush (TYPE_4__*) ; 

__attribute__((used)) static int qdmc_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    QDMCContext *s = avctx->priv_data;
    AVFrame *frame = data;
    GetBitContext gb;
    int ret;

    if (!avpkt->data)
        return 0;
    if (avpkt->size < s->checksum_size)
        return AVERROR_INVALIDDATA;

    s->avctx = avctx;
    frame->nb_samples = s->frame_size;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    if ((ret = init_get_bits8(&gb, avpkt->data, s->checksum_size)) < 0)
        return ret;

    memset(s->nb_tones, 0, sizeof(s->nb_tones));
    memset(s->cur_tone, 0, sizeof(s->cur_tone));

    ret = decode_frame(s, &gb, (int16_t *)frame->data[0]);
    if (ret >= 0) {
        *got_frame_ptr = 1;
        return s->checksum_size;
    }
    qdmc_flush(avctx);
    return ret;
}