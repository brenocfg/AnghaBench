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
struct TYPE_14__ {int gop_size; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {int key_frame; int /*<<< orphan*/  previous_frame; TYPE_1__* avctx; int /*<<< orphan*/  max_buf_size; } ;
struct TYPE_11__ {int frame_number; } ;
typedef  TYPE_2__ QtrleEncContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int av_frame_ref (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  encode_frame (TYPE_2__* const,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtrle_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                              const AVFrame *pict, int *got_packet)
{
    QtrleEncContext * const s = avctx->priv_data;
    int ret;

    if ((ret = ff_alloc_packet2(avctx, pkt, s->max_buf_size, 0)) < 0)
        return ret;

    if (avctx->gop_size == 0 || (s->avctx->frame_number % avctx->gop_size) == 0) {
        /* I-Frame */
        s->key_frame = 1;
    } else {
        /* P-Frame */
        s->key_frame = 0;
    }

    pkt->size = encode_frame(s, pict, pkt->data);

    /* save the current frame */
    av_frame_unref(s->previous_frame);
    ret = av_frame_ref(s->previous_frame, pict);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "cannot add reference\n");
        return ret;
    }

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->key_frame = s->key_frame;
    avctx->coded_frame->pict_type = s->key_frame ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    if (s->key_frame)
        pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}