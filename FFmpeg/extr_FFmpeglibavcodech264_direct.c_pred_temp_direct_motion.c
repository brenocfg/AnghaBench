#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_16__ {int reference; TYPE_1__* parent; } ;
struct TYPE_13__ {TYPE_2__* sps; } ;
struct TYPE_15__ {int b_stride; int mb_stride; size_t* mb2b_xy; TYPE_3__ ps; } ;
struct TYPE_14__ {int mb_xy; int mb_y; int col_parity; int mb_x; int col_fieldoff; int const** map_col_to_list0; int* dist_scale_factor; int*** map_col_to_list0_field; int** dist_scale_factor_field; unsigned int* sub_mb_type; int*** ref_cache; int*** mv_cache; TYPE_9__** ref_list; } ;
struct TYPE_12__ {int direct_8x8_inference_flag; } ;
struct TYPE_11__ {int* mb_type; int** ref_index; int mbaff; int /*<<< orphan*/ ** motion_val; } ;
typedef  TYPE_4__ H264SliceContext ;
typedef  TYPE_5__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN32A (int*,int) ; 
 scalar_t__ FRAME_MBAFF (TYPE_5__ const* const) ; 
 scalar_t__ IS_16X16 (int) ; 
 int IS_8X8 (int) ; 
 int /*<<< orphan*/  IS_DIRECT (unsigned int) ; 
 scalar_t__ IS_INTERLACED (int) ; 
 scalar_t__ IS_INTRA (int) ; 
 scalar_t__ IS_SUB_8X8 (unsigned int) ; 
 int MB_TYPE_16x16 ; 
 int MB_TYPE_16x16_OR_INTRA ; 
 int MB_TYPE_16x8 ; 
 int MB_TYPE_8x16 ; 
 int MB_TYPE_8x8 ; 
 int MB_TYPE_DIRECT2 ; 
 int MB_TYPE_INTERLACED ; 
 int MB_TYPE_L0L1 ; 
 int MB_TYPE_P0L0 ; 
 int MB_TYPE_P0L1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  await_reference_mb_row (TYPE_5__ const* const,TYPE_9__*,int) ; 
 int /*<<< orphan*/  fill_rectangle (int**,int,int,int,int,int) ; 
 int pack16to32 (int,int) ; 
 size_t* scan8 ; 

__attribute__((used)) static void pred_temp_direct_motion(const H264Context *const h, H264SliceContext *sl,
                                    int *mb_type)
{
    int b8_stride = 2;
    int b4_stride = h->b_stride;
    int mb_xy = sl->mb_xy, mb_y = sl->mb_y;
    int mb_type_col[2];
    const int16_t (*l1mv0)[2], (*l1mv1)[2];
    const int8_t *l1ref0, *l1ref1;
    const int is_b8x8 = IS_8X8(*mb_type);
    unsigned int sub_mb_type;
    int i8, i4;

    assert(sl->ref_list[1][0].reference & 3);

    await_reference_mb_row(h, &sl->ref_list[1][0],
                           sl->mb_y + !!IS_INTERLACED(*mb_type));

    if (IS_INTERLACED(sl->ref_list[1][0].parent->mb_type[mb_xy])) { // AFL/AFR/FR/FL -> AFL/FL
        if (!IS_INTERLACED(*mb_type)) {                    //     AFR/FR    -> AFL/FL
            mb_y  = (sl->mb_y & ~1) + sl->col_parity;
            mb_xy = sl->mb_x +
                    ((sl->mb_y & ~1) + sl->col_parity) * h->mb_stride;
            b8_stride = 0;
        } else {
            mb_y  += sl->col_fieldoff;
            mb_xy += h->mb_stride * sl->col_fieldoff; // non-zero for FL -> FL & differ parity
        }
        goto single_col;
    } else {                                        // AFL/AFR/FR/FL -> AFR/FR
        if (IS_INTERLACED(*mb_type)) {              // AFL       /FL -> AFR/FR
            mb_y           = sl->mb_y & ~1;
            mb_xy          = sl->mb_x + (sl->mb_y & ~1) * h->mb_stride;
            mb_type_col[0] = sl->ref_list[1][0].parent->mb_type[mb_xy];
            mb_type_col[1] = sl->ref_list[1][0].parent->mb_type[mb_xy + h->mb_stride];
            b8_stride      = 2 + 4 * h->mb_stride;
            b4_stride     *= 6;
            if (IS_INTERLACED(mb_type_col[0]) !=
                IS_INTERLACED(mb_type_col[1])) {
                mb_type_col[0] &= ~MB_TYPE_INTERLACED;
                mb_type_col[1] &= ~MB_TYPE_INTERLACED;
            }

            sub_mb_type = MB_TYPE_16x16 | MB_TYPE_P0L0 | MB_TYPE_P0L1 |
                          MB_TYPE_DIRECT2;                  /* B_SUB_8x8 */

            if ((mb_type_col[0] & MB_TYPE_16x16_OR_INTRA) &&
                (mb_type_col[1] & MB_TYPE_16x16_OR_INTRA) &&
                !is_b8x8) {
                *mb_type |= MB_TYPE_16x8 | MB_TYPE_L0L1 |
                            MB_TYPE_DIRECT2;                /* B_16x8 */
            } else {
                *mb_type |= MB_TYPE_8x8 | MB_TYPE_L0L1;
            }
        } else {                                    //     AFR/FR    -> AFR/FR
single_col:
            mb_type_col[0]     =
                mb_type_col[1] = sl->ref_list[1][0].parent->mb_type[mb_xy];

            sub_mb_type = MB_TYPE_16x16 | MB_TYPE_P0L0 | MB_TYPE_P0L1 |
                          MB_TYPE_DIRECT2;                  /* B_SUB_8x8 */
            if (!is_b8x8 && (mb_type_col[0] & MB_TYPE_16x16_OR_INTRA)) {
                *mb_type |= MB_TYPE_16x16 | MB_TYPE_P0L0 | MB_TYPE_P0L1 |
                            MB_TYPE_DIRECT2;                /* B_16x16 */
            } else if (!is_b8x8 &&
                       (mb_type_col[0] & (MB_TYPE_16x8 | MB_TYPE_8x16))) {
                *mb_type |= MB_TYPE_L0L1 | MB_TYPE_DIRECT2 |
                            (mb_type_col[0] & (MB_TYPE_16x8 | MB_TYPE_8x16));
            } else {
                if (!h->ps.sps->direct_8x8_inference_flag) {
                    /* FIXME: save sub mb types from previous frames (or derive
                     * from MVs) so we know exactly what block size to use */
                    sub_mb_type = MB_TYPE_8x8 | MB_TYPE_P0L0 | MB_TYPE_P0L1 |
                                  MB_TYPE_DIRECT2;          /* B_SUB_4x4 */
                }
                *mb_type |= MB_TYPE_8x8 | MB_TYPE_L0L1;
            }
        }
    }

    await_reference_mb_row(h, &sl->ref_list[1][0], mb_y);

    l1mv0  = (void*)&sl->ref_list[1][0].parent->motion_val[0][h->mb2b_xy[mb_xy]];
    l1mv1  = (void*)&sl->ref_list[1][0].parent->motion_val[1][h->mb2b_xy[mb_xy]];
    l1ref0 = &sl->ref_list[1][0].parent->ref_index[0][4 * mb_xy];
    l1ref1 = &sl->ref_list[1][0].parent->ref_index[1][4 * mb_xy];
    if (!b8_stride) {
        if (sl->mb_y & 1) {
            l1ref0 += 2;
            l1ref1 += 2;
            l1mv0  += 2 * b4_stride;
            l1mv1  += 2 * b4_stride;
        }
    }

    {
        const int *map_col_to_list0[2] = { sl->map_col_to_list0[0],
                                           sl->map_col_to_list0[1] };
        const int *dist_scale_factor = sl->dist_scale_factor;
        int ref_offset;

        if (FRAME_MBAFF(h) && IS_INTERLACED(*mb_type)) {
            map_col_to_list0[0] = sl->map_col_to_list0_field[sl->mb_y & 1][0];
            map_col_to_list0[1] = sl->map_col_to_list0_field[sl->mb_y & 1][1];
            dist_scale_factor   = sl->dist_scale_factor_field[sl->mb_y & 1];
        }
        ref_offset = (sl->ref_list[1][0].parent->mbaff << 4) & (mb_type_col[0] >> 3);

        if (IS_INTERLACED(*mb_type) != IS_INTERLACED(mb_type_col[0])) {
            int y_shift = 2 * !IS_INTERLACED(*mb_type);
            assert(h->ps.sps->direct_8x8_inference_flag);

            for (i8 = 0; i8 < 4; i8++) {
                const int x8 = i8 & 1;
                const int y8 = i8 >> 1;
                int ref0, scale;
                const int16_t (*l1mv)[2] = l1mv0;

                if (is_b8x8 && !IS_DIRECT(sl->sub_mb_type[i8]))
                    continue;
                sl->sub_mb_type[i8] = sub_mb_type;

                fill_rectangle(&sl->ref_cache[1][scan8[i8 * 4]], 2, 2, 8, 0, 1);
                if (IS_INTRA(mb_type_col[y8])) {
                    fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8, 0, 1);
                    fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8, 0, 4);
                    fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8, 0, 4);
                    continue;
                }

                ref0 = l1ref0[x8 + y8 * b8_stride];
                if (ref0 >= 0)
                    ref0 = map_col_to_list0[0][ref0 + ref_offset];
                else {
                    ref0 = map_col_to_list0[1][l1ref1[x8 + y8 * b8_stride] +
                                               ref_offset];
                    l1mv = l1mv1;
                }
                scale = dist_scale_factor[ref0];
                fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8,
                               ref0, 1);

                {
                    const int16_t *mv_col = l1mv[x8 * 3 + y8 * b4_stride];
                    int my_col            = (mv_col[1] * (1 << y_shift)) / 2;
                    int mx                = (scale * mv_col[0] + 128) >> 8;
                    int my                = (scale * my_col    + 128) >> 8;
                    fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8,
                                   pack16to32(mx, my), 4);
                    fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8,
                                   pack16to32(mx - mv_col[0], my - my_col), 4);
                }
            }
            return;
        }

        /* one-to-one mv scaling */

        if (IS_16X16(*mb_type)) {
            int ref, mv0, mv1;

            fill_rectangle(&sl->ref_cache[1][scan8[0]], 4, 4, 8, 0, 1);
            if (IS_INTRA(mb_type_col[0])) {
                ref = mv0 = mv1 = 0;
            } else {
                const int ref0 = l1ref0[0] >= 0 ? map_col_to_list0[0][l1ref0[0] + ref_offset]
                                                : map_col_to_list0[1][l1ref1[0] + ref_offset];
                const int scale = dist_scale_factor[ref0];
                const int16_t *mv_col = l1ref0[0] >= 0 ? l1mv0[0] : l1mv1[0];
                int mv_l0[2];
                mv_l0[0] = (scale * mv_col[0] + 128) >> 8;
                mv_l0[1] = (scale * mv_col[1] + 128) >> 8;
                ref      = ref0;
                mv0      = pack16to32(mv_l0[0], mv_l0[1]);
                mv1      = pack16to32(mv_l0[0] - mv_col[0], mv_l0[1] - mv_col[1]);
            }
            fill_rectangle(&sl->ref_cache[0][scan8[0]], 4, 4, 8, ref, 1);
            fill_rectangle(&sl->mv_cache[0][scan8[0]], 4, 4, 8, mv0, 4);
            fill_rectangle(&sl->mv_cache[1][scan8[0]], 4, 4, 8, mv1, 4);
        } else {
            for (i8 = 0; i8 < 4; i8++) {
                const int x8 = i8 & 1;
                const int y8 = i8 >> 1;
                int ref0, scale;
                const int16_t (*l1mv)[2] = l1mv0;

                if (is_b8x8 && !IS_DIRECT(sl->sub_mb_type[i8]))
                    continue;
                sl->sub_mb_type[i8] = sub_mb_type;
                fill_rectangle(&sl->ref_cache[1][scan8[i8 * 4]], 2, 2, 8, 0, 1);
                if (IS_INTRA(mb_type_col[0])) {
                    fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8, 0, 1);
                    fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8, 0, 4);
                    fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8, 0, 4);
                    continue;
                }

                assert(b8_stride == 2);
                ref0 = l1ref0[i8];
                if (ref0 >= 0)
                    ref0 = map_col_to_list0[0][ref0 + ref_offset];
                else {
                    ref0 = map_col_to_list0[1][l1ref1[i8] + ref_offset];
                    l1mv = l1mv1;
                }
                scale = dist_scale_factor[ref0];

                fill_rectangle(&sl->ref_cache[0][scan8[i8 * 4]], 2, 2, 8,
                               ref0, 1);
                if (IS_SUB_8X8(sub_mb_type)) {
                    const int16_t *mv_col = l1mv[x8 * 3 + y8 * 3 * b4_stride];
                    int mx                = (scale * mv_col[0] + 128) >> 8;
                    int my                = (scale * mv_col[1] + 128) >> 8;
                    fill_rectangle(&sl->mv_cache[0][scan8[i8 * 4]], 2, 2, 8,
                                   pack16to32(mx, my), 4);
                    fill_rectangle(&sl->mv_cache[1][scan8[i8 * 4]], 2, 2, 8,
                                   pack16to32(mx - mv_col[0], my - mv_col[1]), 4);
                } else {
                    for (i4 = 0; i4 < 4; i4++) {
                        const int16_t *mv_col = l1mv[x8 * 2 + (i4 & 1) +
                                                     (y8 * 2 + (i4 >> 1)) * b4_stride];
                        int16_t *mv_l0 = sl->mv_cache[0][scan8[i8 * 4 + i4]];
                        mv_l0[0] = (scale * mv_col[0] + 128) >> 8;
                        mv_l0[1] = (scale * mv_col[1] + 128) >> 8;
                        AV_WN32A(sl->mv_cache[1][scan8[i8 * 4 + i4]],
                                 pack16to32(mv_l0[0] - mv_col[0],
                                            mv_l0[1] - mv_col[1]));
                    }
                }
            }
        }
    }
}