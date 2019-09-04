#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_22__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {char sliceType; } ;
struct TYPE_28__ {TYPE_3__ frameData; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  quantOffsets; int /*<<< orphan*/  sliceType; int /*<<< orphan*/  bitDepth; int /*<<< orphan*/ * stride; int /*<<< orphan*/ * planes; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ x265_picture ;
struct TYPE_29__ {int /*<<< orphan*/  type; scalar_t__ sizeBytes; int /*<<< orphan*/  payload; } ;
typedef  TYPE_5__ x265_nal ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_30__ {int /*<<< orphan*/  encoder; TYPE_2__* api; scalar_t__ forced_idr; int /*<<< orphan*/  params; } ;
typedef  TYPE_6__ libx265Context ;
struct TYPE_33__ {int /*<<< orphan*/  pix_fmt; TYPE_6__* priv_data; } ;
struct TYPE_32__ {scalar_t__ pict_type; int /*<<< orphan*/  pts; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_26__ {int (* encoder_encode ) (int /*<<< orphan*/ ,TYPE_5__**,int*,TYPE_4__*,TYPE_4__*) ;int /*<<< orphan*/  (* picture_init ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct TYPE_25__ {TYPE_1__* comp; } ;
struct TYPE_24__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_7__ AVPacket ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PKT_FLAG_DISPOSABLE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  X265_TYPE_AUTO ; 
 int /*<<< orphan*/  X265_TYPE_B ; 
 int /*<<< orphan*/  X265_TYPE_I ; 
 int /*<<< orphan*/  X265_TYPE_IDR ; 
 int /*<<< orphan*/  X265_TYPE_P ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_22__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_alloc_packet2 (TYPE_9__*,TYPE_7__*,int,int) ; 
 scalar_t__ is_keyframe (int /*<<< orphan*/ ) ; 
 int libx265_encode_set_roi (TYPE_6__*,TYPE_8__ const*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int stub2 (int /*<<< orphan*/ ,TYPE_5__**,int*,TYPE_4__*,TYPE_4__*) ; 

__attribute__((used)) static int libx265_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                const AVFrame *pic, int *got_packet)
{
    libx265Context *ctx = avctx->priv_data;
    x265_picture x265pic;
    x265_picture x265pic_out = { 0 };
    x265_nal *nal;
    uint8_t *dst;
    int payload = 0;
    int nnal;
    int ret;
    int i;

    ctx->api->picture_init(ctx->params, &x265pic);

    if (pic) {
        for (i = 0; i < 3; i++) {
           x265pic.planes[i] = pic->data[i];
           x265pic.stride[i] = pic->linesize[i];
        }

        x265pic.pts      = pic->pts;
        x265pic.bitDepth = av_pix_fmt_desc_get(avctx->pix_fmt)->comp[0].depth;

        x265pic.sliceType = pic->pict_type == AV_PICTURE_TYPE_I ?
                                              (ctx->forced_idr ? X265_TYPE_IDR : X265_TYPE_I) :
                            pic->pict_type == AV_PICTURE_TYPE_P ? X265_TYPE_P :
                            pic->pict_type == AV_PICTURE_TYPE_B ? X265_TYPE_B :
                            X265_TYPE_AUTO;

        ret = libx265_encode_set_roi(ctx, pic, &x265pic);
        if (ret < 0)
            return ret;
    }

    ret = ctx->api->encoder_encode(ctx->encoder, &nal, &nnal,
                                   pic ? &x265pic : NULL, &x265pic_out);

    av_freep(&x265pic.quantOffsets);

    if (ret < 0)
        return AVERROR_EXTERNAL;

    if (!nnal)
        return 0;

    for (i = 0; i < nnal; i++)
        payload += nal[i].sizeBytes;

    ret = ff_alloc_packet2(avctx, pkt, payload, payload);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error getting output packet.\n");
        return ret;
    }
    dst = pkt->data;

    for (i = 0; i < nnal; i++) {
        memcpy(dst, nal[i].payload, nal[i].sizeBytes);
        dst += nal[i].sizeBytes;

        if (is_keyframe(nal[i].type))
            pkt->flags |= AV_PKT_FLAG_KEY;
    }

    pkt->pts = x265pic_out.pts;
    pkt->dts = x265pic_out.dts;

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    switch (x265pic_out.sliceType) {
    case X265_TYPE_IDR:
    case X265_TYPE_I:
        avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
        break;
    case X265_TYPE_P:
        avctx->coded_frame->pict_type = AV_PICTURE_TYPE_P;
        break;
    case X265_TYPE_B:
        avctx->coded_frame->pict_type = AV_PICTURE_TYPE_B;
        break;
    }
FF_ENABLE_DEPRECATION_WARNINGS
#endif

#if X265_BUILD >= 130
    if (x265pic_out.sliceType == X265_TYPE_B)
#else
    if (x265pic_out.frameData.sliceType == 'b')
#endif
        pkt->flags |= AV_PKT_FLAG_DISPOSABLE;

    *got_packet = 1;
    return 0;
}