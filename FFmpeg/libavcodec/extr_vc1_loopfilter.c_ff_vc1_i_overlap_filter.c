#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int mb_x; int mb_y; int mb_stride; int mb_width; scalar_t__ first_slice_line; TYPE_1__* avctx; } ;
struct TYPE_8__ {size_t topleft_blk_idx; size_t top_blk_idx; size_t left_blk_idx; size_t cur_blk_idx; int pq; scalar_t__ profile; scalar_t__ condover; scalar_t__ fcm; scalar_t__* over_flags_plane; scalar_t__* fieldtx_plane; int /*<<< orphan*/ *** block; TYPE_3__ s; } ;
typedef  TYPE_2__ VC1Context ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ CONDOVER_ALL ; 
 scalar_t__ CONFIG_GRAY ; 
 scalar_t__ ILACE_FRAME ; 
 scalar_t__ PROFILE_ADVANCED ; 
 int /*<<< orphan*/  vc1_h_overlap_filter (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  vc1_v_overlap_filter (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 

void ff_vc1_i_overlap_filter(VC1Context *v)
{
    MpegEncContext *s = &v->s;
    int16_t (*topleft_blk)[64], (*top_blk)[64], (*left_blk)[64], (*cur_blk)[64];
    int block_count = CONFIG_GRAY && (s->avctx->flags & AV_CODEC_FLAG_GRAY) ? 4 : 6;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int i;

    topleft_blk = v->block[v->topleft_blk_idx];
    top_blk = v->block[v->top_blk_idx];
    left_blk = v->block[v->left_blk_idx];
    cur_blk = v->block[v->cur_blk_idx];

    /* Within a MB, the horizontal overlap always runs before the vertical.
     * To accomplish that, we run the H on the left and internal vertical
     * borders of the currently decoded MB. Then, we wait for the next overlap
     * iteration to do H overlap on the right edge of this MB, before moving
     * over and running the V overlap on the top and internal horizontal
     * borders. Therefore, the H overlap trails by one MB col and the
     * V overlap trails by one MB row. This is reflected in the time at which
     * we run the put_pixels loop, i.e. delayed by one row and one column. */
    for (i = 0; i < block_count; i++) {
        if (s->mb_x == 0 && (i & 5) != 1)
            continue;

        if (v->pq >= 9 || (v->profile == PROFILE_ADVANCED &&
                           (v->condover == CONDOVER_ALL ||
                            (v->over_flags_plane[mb_pos] &&
                             ((i & 5) == 1 || v->over_flags_plane[mb_pos - 1])))))
            vc1_h_overlap_filter(v,
                                 s->mb_x ? left_blk : cur_blk, cur_blk,
                                 v->fcm == ILACE_FRAME && s->mb_x && v->fieldtx_plane[mb_pos - 1],
                                 v->fcm == ILACE_FRAME && v->fieldtx_plane[mb_pos],
                                 i);
    }

    if (v->fcm != ILACE_FRAME)
        for (i = 0; i < block_count; i++) {
            if (s->first_slice_line && !(i & 2))
                continue;

            if (s->mb_x &&
                (v->pq >= 9 || (v->profile == PROFILE_ADVANCED &&
                                (v->condover == CONDOVER_ALL ||
                                 (v->over_flags_plane[mb_pos - 1] &&
                                  ((i & 2) || v->over_flags_plane[mb_pos - 1 - s->mb_stride]))))))
                vc1_v_overlap_filter(v, s->first_slice_line ? left_blk : topleft_blk, left_blk, i);
            if (s->mb_x == s->mb_width - 1 &&
                (v->pq >= 9 || (v->profile == PROFILE_ADVANCED &&
                                (v->condover == CONDOVER_ALL ||
                                 (v->over_flags_plane[mb_pos] &&
                                  ((i & 2) || v->over_flags_plane[mb_pos - s->mb_stride]))))))
                vc1_v_overlap_filter(v, s->first_slice_line ? cur_blk : top_blk, cur_blk, i);
        }
}