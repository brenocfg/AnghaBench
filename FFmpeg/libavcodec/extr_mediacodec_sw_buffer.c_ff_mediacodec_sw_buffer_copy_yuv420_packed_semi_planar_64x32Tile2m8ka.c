#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t width; size_t* linesize; size_t height; scalar_t__* data; } ;
typedef  int /*<<< orphan*/  MediaCodecDecContext ;
typedef  int /*<<< orphan*/  FFAMediaCodecBufferInfo ;
typedef  TYPE_1__ AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 size_t QCOM_TILE_GROUP_SIZE ; 
 size_t QCOM_TILE_HEIGHT ; 
 size_t const QCOM_TILE_SIZE ; 
 size_t QCOM_TILE_WIDTH ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 size_t const qcom_tile_pos (size_t,size_t,size_t const,size_t const) ; 

void ff_mediacodec_sw_buffer_copy_yuv420_packed_semi_planar_64x32Tile2m8ka(AVCodecContext *avctx,
                                                                           MediaCodecDecContext *s,
                                                                           uint8_t *data,
                                                                           size_t size,
                                                                           FFAMediaCodecBufferInfo *info,
                                                                           AVFrame *frame)
{
    size_t width = frame->width;
    size_t linesize = frame->linesize[0];
    size_t height = frame->height;

    const size_t tile_w = (width - 1) / QCOM_TILE_WIDTH + 1;
    const size_t tile_w_align = (tile_w + 1) & ~1;
    const size_t tile_h_luma = (height - 1) / QCOM_TILE_HEIGHT + 1;
    const size_t tile_h_chroma = (height / 2 - 1) / QCOM_TILE_HEIGHT + 1;

    size_t luma_size = tile_w_align * tile_h_luma * QCOM_TILE_SIZE;
    if((luma_size % QCOM_TILE_GROUP_SIZE) != 0)
        luma_size = (((luma_size - 1) / QCOM_TILE_GROUP_SIZE) + 1) * QCOM_TILE_GROUP_SIZE;

    for(size_t y = 0; y < tile_h_luma; y++) {
        size_t row_width = width;
        for(size_t x = 0; x < tile_w; x++) {
            size_t tile_width = row_width;
            size_t tile_height = height;
            /* dest luma memory index for this tile */
            size_t luma_idx = y * QCOM_TILE_HEIGHT * linesize + x * QCOM_TILE_WIDTH;
            /* dest chroma memory index for this tile */
            /* XXX: remove divisions */
            size_t chroma_idx = (luma_idx / linesize) * linesize / 2 + (luma_idx % linesize);

            /* luma source pointer for this tile */
            const uint8_t *src_luma  = data
                + qcom_tile_pos(x, y,tile_w_align, tile_h_luma) * QCOM_TILE_SIZE;

            /* chroma source pointer for this tile */
            const uint8_t *src_chroma = data + luma_size
                + qcom_tile_pos(x, y/2, tile_w_align, tile_h_chroma) * QCOM_TILE_SIZE;
            if (y & 1)
                src_chroma += QCOM_TILE_SIZE/2;

            /* account for right columns */
            if (tile_width > QCOM_TILE_WIDTH)
                tile_width = QCOM_TILE_WIDTH;

            /* account for bottom rows */
            if (tile_height > QCOM_TILE_HEIGHT)
                tile_height = QCOM_TILE_HEIGHT;

            tile_height /= 2;
            while (tile_height--) {
                memcpy(frame->data[0] + luma_idx, src_luma, tile_width);
                src_luma += QCOM_TILE_WIDTH;
                luma_idx += linesize;

                memcpy(frame->data[0] + luma_idx, src_luma, tile_width);
                src_luma += QCOM_TILE_WIDTH;
                luma_idx += linesize;

                memcpy(frame->data[1] + chroma_idx, src_chroma, tile_width);
                src_chroma += QCOM_TILE_WIDTH;
                chroma_idx += linesize;
            }
            row_width -= QCOM_TILE_WIDTH;
        }
        height -= QCOM_TILE_HEIGHT;
    }
}