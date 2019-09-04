#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int mb_width; int mb_height; int slice_count; TYPE_1__* slices; scalar_t__ frame_type; } ;
struct TYPE_8__ {int const* data; int mb_x; int mb_y; int mb_count; int data_size; } ;
typedef  TYPE_1__ SliceContext ;
typedef  TYPE_2__ ProresContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_RB16 (int const*) ; 
 unsigned int AV_RB32 (int const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* av_mallocz_array (int,int) ; 
 int av_popcount (int) ; 

__attribute__((used)) static int decode_picture_header(AVCodecContext *avctx, const uint8_t *buf, const int buf_size)
{
    ProresContext *ctx = avctx->priv_data;
    int i, hdr_size, slice_count;
    unsigned pic_data_size;
    int log2_slice_mb_width, log2_slice_mb_height;
    int slice_mb_count, mb_x, mb_y;
    const uint8_t *data_ptr, *index_ptr;

    hdr_size = buf[0] >> 3;
    if (hdr_size < 8 || hdr_size > buf_size) {
        av_log(avctx, AV_LOG_ERROR, "error, wrong picture header size\n");
        return AVERROR_INVALIDDATA;
    }

    pic_data_size = AV_RB32(buf + 1);
    if (pic_data_size > buf_size) {
        av_log(avctx, AV_LOG_ERROR, "error, wrong picture data size\n");
        return AVERROR_INVALIDDATA;
    }

    log2_slice_mb_width  = buf[7] >> 4;
    log2_slice_mb_height = buf[7] & 0xF;
    if (log2_slice_mb_width > 3 || log2_slice_mb_height) {
        av_log(avctx, AV_LOG_ERROR, "unsupported slice resolution: %dx%d\n",
               1 << log2_slice_mb_width, 1 << log2_slice_mb_height);
        return AVERROR_INVALIDDATA;
    }

    ctx->mb_width  = (avctx->width  + 15) >> 4;
    if (ctx->frame_type)
        ctx->mb_height = (avctx->height + 31) >> 5;
    else
        ctx->mb_height = (avctx->height + 15) >> 4;

    // QT ignores the written value
    // slice_count = AV_RB16(buf + 5);
    slice_count = ctx->mb_height * ((ctx->mb_width >> log2_slice_mb_width) +
                                    av_popcount(ctx->mb_width & (1 << log2_slice_mb_width) - 1));

    if (ctx->slice_count != slice_count || !ctx->slices) {
        av_freep(&ctx->slices);
        ctx->slice_count = 0;
        ctx->slices = av_mallocz_array(slice_count, sizeof(*ctx->slices));
        if (!ctx->slices)
            return AVERROR(ENOMEM);
        ctx->slice_count = slice_count;
    }

    if (!slice_count)
        return AVERROR(EINVAL);

    if (hdr_size + slice_count*2 > buf_size) {
        av_log(avctx, AV_LOG_ERROR, "error, wrong slice count\n");
        return AVERROR_INVALIDDATA;
    }

    // parse slice information
    index_ptr = buf + hdr_size;
    data_ptr  = index_ptr + slice_count*2;

    slice_mb_count = 1 << log2_slice_mb_width;
    mb_x = 0;
    mb_y = 0;

    for (i = 0; i < slice_count; i++) {
        SliceContext *slice = &ctx->slices[i];

        slice->data = data_ptr;
        data_ptr += AV_RB16(index_ptr + i*2);

        while (ctx->mb_width - mb_x < slice_mb_count)
            slice_mb_count >>= 1;

        slice->mb_x = mb_x;
        slice->mb_y = mb_y;
        slice->mb_count = slice_mb_count;
        slice->data_size = data_ptr - slice->data;

        if (slice->data_size < 6) {
            av_log(avctx, AV_LOG_ERROR, "error, wrong slice data size\n");
            return AVERROR_INVALIDDATA;
        }

        mb_x += slice_mb_count;
        if (mb_x == ctx->mb_width) {
            slice_mb_count = 1 << log2_slice_mb_width;
            mb_x = 0;
            mb_y++;
        }
        if (data_ptr > buf + buf_size) {
            av_log(avctx, AV_LOG_ERROR, "error, slice out of bounds\n");
            return AVERROR_INVALIDDATA;
        }
    }

    if (mb_x || mb_y != ctx->mb_height) {
        av_log(avctx, AV_LOG_ERROR, "error wrong mb count y %d h %d\n",
               mb_y, ctx->mb_height);
        return AVERROR_INVALIDDATA;
    }

    return pic_data_size;
}