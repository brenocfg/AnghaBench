#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {scalar_t__ frame_number; scalar_t__ gop_size; TYPE_1__* priv_data; } ;
struct TYPE_16__ {int* linesize; scalar_t__* data; } ;
struct TYPE_15__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int image_height; scalar_t__ last_key_frame; int image_width; int /*<<< orphan*/ * previous_frame; } ;
typedef  TYPE_1__ FlashSVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/  encode_bitstream (TYPE_1__* const,TYPE_3__ const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int*) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_4__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int flashsv_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                const AVFrame *pict, int *got_packet)
{
    FlashSVContext * const s = avctx->priv_data;
    const AVFrame * const p = pict;
    uint8_t *pfptr;
    int res;
    int I_frame = 0;
    int opt_w = 4, opt_h = 4;

    /* First frame needs to be a keyframe */
    if (avctx->frame_number == 0) {
        s->previous_frame = av_mallocz(FFABS(p->linesize[0]) * s->image_height);
        if (!s->previous_frame) {
            av_log(avctx, AV_LOG_ERROR, "Memory allocation failed.\n");
            return AVERROR(ENOMEM);
        }
        I_frame = 1;
    }

    if (p->linesize[0] < 0)
        pfptr = s->previous_frame - (s->image_height - 1) * p->linesize[0];
    else
        pfptr = s->previous_frame;

    /* Check the placement of keyframes */
    if (avctx->gop_size > 0 &&
        avctx->frame_number >= s->last_key_frame + avctx->gop_size) {
        I_frame = 1;
    }

    if ((res = ff_alloc_packet2(avctx, pkt, s->image_width * s->image_height * 3, 0)) < 0)
        return res;

    pkt->size = encode_bitstream(s, p, pkt->data, pkt->size, opt_w * 16, opt_h * 16,
                                 pfptr, &I_frame);

    //save the current frame
    if (p->linesize[0] > 0)
        memcpy(s->previous_frame, p->data[0], s->image_height * p->linesize[0]);
    else
        memcpy(s->previous_frame,
               p->data[0] + p->linesize[0] * (s->image_height - 1),
               s->image_height * FFABS(p->linesize[0]));

    //mark the frame type so the muxer can mux it correctly
    if (I_frame) {
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        avctx->coded_frame->pict_type      = AV_PICTURE_TYPE_I;
        avctx->coded_frame->key_frame      = 1;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
        s->last_key_frame = avctx->frame_number;
        ff_dlog(avctx, "Inserting keyframe at frame %d\n", avctx->frame_number);
    } else {
#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
        avctx->coded_frame->pict_type = AV_PICTURE_TYPE_P;
        avctx->coded_frame->key_frame = 0;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
    }

    if (I_frame)
        pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;

    return 0;
}