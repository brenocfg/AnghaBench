#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  gb; } ;
struct TYPE_7__ {int height; int width; TYPE_3__* priv_data; } ;
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;
typedef  TYPE_3__ ARBCContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int) ; 
 int FFMIN (int const,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_tileX(AVCodecContext *avctx, int tile_width, int tile_height,
                       int color, AVFrame *frame)
{
    ARBCContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    const int step_h = tile_height / 4;
    const int step_w = tile_width / 4;
    int nb_tiles = bytestream2_get_le16(gb);
    int h = avctx->height - 1;
    int pixels_overwritten = 0;

    if ((avctx->width / tile_width + 1) * (avctx->height / tile_height + 1) < nb_tiles)
        return 0;

    for (int i = 0; i < nb_tiles; i++) {
        int y = bytestream2_get_byte(gb);
        int x = bytestream2_get_byte(gb);
        uint16_t mask = bytestream2_get_le16(gb);
        int start_y = y * tile_height, start_x = x * tile_width;
        int end_y = start_y + tile_height, end_x = start_x + tile_width;

        if (start_x >= avctx->width || start_y >= avctx->height)
            continue;

        for (int j = start_y; j < end_y; j += step_h) {
            for (int k = start_x; k < end_x; k += step_w) {
                if (mask & 0x8000U) {
                    for (int m = 0; m < step_h; m++) {
                        for (int n = 0; n < step_w; n++) {
                            if (j + m >= avctx->height || k + n >= avctx->width)
                                continue;
                            AV_WB24(&frame->data[0][frame->linesize[0] * (h - (j + m)) + 3 * (k + n)], color);
                        }
                    }
                    pixels_overwritten += FFMIN(step_h, avctx->height - j) * FFMIN(step_w, avctx->width - k);
                }
                mask = mask << 1;
            }
        }
    }
    return pixels_overwritten;
}