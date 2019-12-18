#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_13__ {TYPE_4__* priv_data; TYPE_1__* internal; } ;
struct TYPE_12__ {scalar_t__ intra_pic_flag; } ;
struct TYPE_11__ {TYPE_3__* slice_ctx; } ;
struct TYPE_10__ {scalar_t__ slice_type; } ;
struct TYPE_9__ {int* bitstream; int bitstream_len; int* slice_offsets; int nb_slices; int /*<<< orphan*/  slice_offsets_allocated; int /*<<< orphan*/  bitstream_allocated; TYPE_5__ pic_params; } ;
struct TYPE_8__ {TYPE_2__* hwaccel_priv_data; } ;
typedef  TYPE_2__ NVDECContext ;
typedef  TYPE_3__ H264SliceContext ;
typedef  TYPE_4__ H264Context ;
typedef  TYPE_5__ CUVIDPICPARAMS ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_SI ; 
 int /*<<< orphan*/  AV_WB24 (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_fast_realloc (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int nvdec_h264_decode_slice(AVCodecContext *avctx, const uint8_t *buffer,
                                   uint32_t size)
{
    NVDECContext *ctx = avctx->internal->hwaccel_priv_data;
    CUVIDPICPARAMS *pp = &ctx->pic_params;
    const H264Context *h = avctx->priv_data;
    const H264SliceContext *sl = &h->slice_ctx[0];
    void *tmp;

    tmp = av_fast_realloc(ctx->bitstream, &ctx->bitstream_allocated,
                          ctx->bitstream_len + size + 3);
    if (!tmp)
        return AVERROR(ENOMEM);
    ctx->bitstream = tmp;

    tmp = av_fast_realloc(ctx->slice_offsets, &ctx->slice_offsets_allocated,
                          (ctx->nb_slices + 1) * sizeof(*ctx->slice_offsets));
    if (!tmp)
        return AVERROR(ENOMEM);
    ctx->slice_offsets = tmp;

    AV_WB24(ctx->bitstream + ctx->bitstream_len, 1);
    memcpy(ctx->bitstream + ctx->bitstream_len + 3, buffer, size);
    ctx->slice_offsets[ctx->nb_slices] = ctx->bitstream_len ;
    ctx->bitstream_len += size + 3;
    ctx->nb_slices++;

    if (sl->slice_type != AV_PICTURE_TYPE_I && sl->slice_type != AV_PICTURE_TYPE_SI)
        pp->intra_pic_flag = 0;

    return 0;
}