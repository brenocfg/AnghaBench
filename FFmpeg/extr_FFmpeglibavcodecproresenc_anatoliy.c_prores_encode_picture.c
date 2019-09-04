#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int width; int height; size_t profile; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_interlaced; } ;
typedef  TYPE_1__ ProresContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB16 (int*,int) ; 
 int /*<<< orphan*/  AV_WB32 (int*,int) ; 
 int DEFAULT_SLICE_MB_WIDTH ; 
 int av_log2 (int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int**,int) ; 
 int encode_slice (TYPE_2__*,int /*<<< orphan*/  const*,int,int,int,int*,int,int,int*,int /*<<< orphan*/ ,int const) ; 
 int* qp_start_table ; 

__attribute__((used)) static int prores_encode_picture(AVCodecContext *avctx, const AVFrame *pic,
        uint8_t *buf, const int buf_size, const int picture_index, const int is_top_field)
{
    ProresContext *ctx = avctx->priv_data;
    int mb_width = (avctx->width + 15) >> 4;
    int hdr_size, sl_size, i;
    int mb_y, sl_data_size, qp, mb_height, picture_height, unsafe_mb_height_limit;
    int unsafe_bot, unsafe_right;
    uint8_t *sl_data, *sl_data_sizes;
    int slice_per_line = 0, rem = mb_width;

    if (!ctx->is_interlaced) { /* progressive encoding */
        mb_height = (avctx->height + 15) >> 4;
        unsafe_mb_height_limit = mb_height;
    } else {
        if (is_top_field) {
            picture_height = (avctx->height + 1) / 2;
        } else {
            picture_height = avctx->height / 2;
        }
        mb_height = (picture_height + 15) >> 4;
        unsafe_mb_height_limit = mb_height;
    }

    for (i = av_log2(DEFAULT_SLICE_MB_WIDTH); i >= 0; --i) {
        slice_per_line += rem >> i;
        rem &= (1 << i) - 1;
    }

    qp = qp_start_table[avctx->profile];
    hdr_size = 8; sl_data_size = buf_size - hdr_size;
    sl_data_sizes = buf + hdr_size;
    sl_data = sl_data_sizes + (slice_per_line * mb_height * 2);
    for (mb_y = 0; mb_y < mb_height; mb_y++) {
        int mb_x = 0;
        int slice_mb_count = DEFAULT_SLICE_MB_WIDTH;
        while (mb_x < mb_width) {
            while (mb_width - mb_x < slice_mb_count)
                slice_mb_count >>= 1;

            unsafe_bot = (avctx->height & 0xf) && (mb_y == unsafe_mb_height_limit - 1);
            unsafe_right = (avctx->width & 0xf) && (mb_x + slice_mb_count == mb_width);

            sl_size = encode_slice(avctx, pic, mb_x, mb_y, slice_mb_count,
                    sl_data, sl_data_size, unsafe_bot || unsafe_right, &qp, ctx->is_interlaced, is_top_field);
            if (sl_size < 0){
                return sl_size;
            }

            bytestream_put_be16(&sl_data_sizes, sl_size);
            sl_data           += sl_size;
            sl_data_size      -= sl_size;
            mb_x              += slice_mb_count;
        }
    }

    buf[0] = hdr_size << 3;
    AV_WB32(buf + 1, sl_data - buf);
    AV_WB16(buf + 5, slice_per_line * mb_height); /* picture size */
    buf[7] = av_log2(DEFAULT_SLICE_MB_WIDTH) << 4; /* number of slices */

    return sl_data - buf;
}