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
typedef  int ptrdiff_t ;
typedef  int int16_t ;
struct TYPE_5__ {int*** motion_val; int /*<<< orphan*/ * mb_type; } ;
struct TYPE_6__ {int* error_status_table; int mb_stride; TYPE_1__ cur_pic; } ;
typedef  TYPE_2__ ERContext ;

/* Variables and functions */
 int ER_MB_ERROR ; 
 int FFABS (int) ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int IS_INTRA (int /*<<< orphan*/ ) ; 
 int MAX_NEG_CROP ; 
 int* ff_crop_tab ; 
 int /*<<< orphan*/  set_mv_strides (TYPE_2__*,int*,int*) ; 

__attribute__((used)) static void h_block_filter(ERContext *s, uint8_t *dst, int w,
                           int h, ptrdiff_t stride, int is_luma)
{
    int b_x, b_y;
    ptrdiff_t mvx_stride, mvy_stride;
    const uint8_t *cm = ff_crop_tab + MAX_NEG_CROP;
    set_mv_strides(s, &mvx_stride, &mvy_stride);
    mvx_stride >>= is_luma;
    mvy_stride *= mvx_stride;

    for (b_y = 0; b_y < h; b_y++) {
        for (b_x = 0; b_x < w - 1; b_x++) {
            int y;
            int left_status  = s->error_status_table[( b_x      >> is_luma) + (b_y >> is_luma) * s->mb_stride];
            int right_status = s->error_status_table[((b_x + 1) >> is_luma) + (b_y >> is_luma) * s->mb_stride];
            int left_intra   = IS_INTRA(s->cur_pic.mb_type[( b_x      >> is_luma) + (b_y >> is_luma) * s->mb_stride]);
            int right_intra  = IS_INTRA(s->cur_pic.mb_type[((b_x + 1) >> is_luma) + (b_y >> is_luma) * s->mb_stride]);
            int left_damage  = left_status & ER_MB_ERROR;
            int right_damage = right_status & ER_MB_ERROR;
            int offset       = b_x * 8 + b_y * stride * 8;
            int16_t *left_mv  = s->cur_pic.motion_val[0][mvy_stride * b_y + mvx_stride *  b_x];
            int16_t *right_mv = s->cur_pic.motion_val[0][mvy_stride * b_y + mvx_stride * (b_x + 1)];
            if (!(left_damage || right_damage))
                continue; // both undamaged
            if ((!left_intra) && (!right_intra) &&
                FFABS(left_mv[0] - right_mv[0]) +
                FFABS(left_mv[1] + right_mv[1]) < 2)
                continue;

            for (y = 0; y < 8; y++) {
                int a, b, c, d;

                a = dst[offset + 7 + y * stride] - dst[offset + 6 + y * stride];
                b = dst[offset + 8 + y * stride] - dst[offset + 7 + y * stride];
                c = dst[offset + 9 + y * stride] - dst[offset + 8 + y * stride];

                d = FFABS(b) - ((FFABS(a) + FFABS(c) + 1) >> 1);
                d = FFMAX(d, 0);
                if (b < 0)
                    d = -d;

                if (d == 0)
                    continue;

                if (!(left_damage && right_damage))
                    d = d * 16 / 9;

                if (left_damage) {
                    dst[offset + 7 + y * stride] = cm[dst[offset + 7 + y * stride] + ((d * 7) >> 4)];
                    dst[offset + 6 + y * stride] = cm[dst[offset + 6 + y * stride] + ((d * 5) >> 4)];
                    dst[offset + 5 + y * stride] = cm[dst[offset + 5 + y * stride] + ((d * 3) >> 4)];
                    dst[offset + 4 + y * stride] = cm[dst[offset + 4 + y * stride] + ((d * 1) >> 4)];
                }
                if (right_damage) {
                    dst[offset + 8 + y * stride] = cm[dst[offset +  8 + y * stride] - ((d * 7) >> 4)];
                    dst[offset + 9 + y * stride] = cm[dst[offset +  9 + y * stride] - ((d * 5) >> 4)];
                    dst[offset + 10+ y * stride] = cm[dst[offset + 10 + y * stride] - ((d * 3) >> 4)];
                    dst[offset + 11+ y * stride] = cm[dst[offset + 11 + y * stride] - ((d * 1) >> 4)];
                }
            }
        }
    }
}