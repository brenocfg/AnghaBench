#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {TYPE_1__* internal; } ;
struct TYPE_6__ {int* bitstream; int bitstream_len; int* slice_offsets; int nb_slices; int /*<<< orphan*/  slice_offsets_allocated; int /*<<< orphan*/  bitstream_allocated; } ;
struct TYPE_5__ {TYPE_2__* hwaccel_priv_data; } ;
typedef  TYPE_2__ NVDECContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB24 (int*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_fast_realloc (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int nvdec_hevc_decode_slice(AVCodecContext *avctx, const uint8_t *buffer,
                                   uint32_t size)
{
    NVDECContext *ctx = avctx->internal->hwaccel_priv_data;
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

    return 0;
}