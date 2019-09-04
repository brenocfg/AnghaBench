#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int member_8; int member_9; int member_10; int member_11; int member_12; int member_13; int member_14; int member_15; } ;
typedef  TYPE_2__ uint8_t ;
struct TYPE_9__ {int* mb_type; } ;
struct TYPE_12__ {int const mb_stride; scalar_t__* slice_table; TYPE_1__ cur_pic; } ;
struct TYPE_11__ {int mb_xy; int topleft_partition; int mb_y; int topleft_mb_xy; int top_mb_xy; int topright_mb_xy; int* left_mb_xy; int topleft_type; int top_type; int topright_type; int* left_type; scalar_t__ slice_num; TYPE_2__ const* left_block; } ;
typedef  TYPE_3__ H264SliceContext ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 scalar_t__ FMO ; 
 scalar_t__ FRAME_MBAFF (TYPE_4__ const*) ; 
 int IS_INTERLACED (int) ; 
 size_t LBOT ; 
 int LEFT_MBS ; 
 size_t LTOP ; 
 int const MB_FIELD (TYPE_3__*) ; 

__attribute__((used)) static void fill_decode_neighbors(const H264Context *h, H264SliceContext *sl, int mb_type)
{
    const int mb_xy = sl->mb_xy;
    int topleft_xy, top_xy, topright_xy, left_xy[LEFT_MBS];
    static const uint8_t left_block_options[4][32] = {
        { 0, 1, 2, 3, 7, 10, 8, 11, 3 + 0 * 4, 3 + 1 * 4, 3 + 2 * 4, 3 + 3 * 4, 1 + 4 * 4, 1 + 8 * 4, 1 + 5 * 4, 1 + 9 * 4 },
        { 2, 2, 3, 3, 8, 11, 8, 11, 3 + 2 * 4, 3 + 2 * 4, 3 + 3 * 4, 3 + 3 * 4, 1 + 5 * 4, 1 + 9 * 4, 1 + 5 * 4, 1 + 9 * 4 },
        { 0, 0, 1, 1, 7, 10, 7, 10, 3 + 0 * 4, 3 + 0 * 4, 3 + 1 * 4, 3 + 1 * 4, 1 + 4 * 4, 1 + 8 * 4, 1 + 4 * 4, 1 + 8 * 4 },
        { 0, 2, 0, 2, 7, 10, 7, 10, 3 + 0 * 4, 3 + 2 * 4, 3 + 0 * 4, 3 + 2 * 4, 1 + 4 * 4, 1 + 8 * 4, 1 + 4 * 4, 1 + 8 * 4 }
    };

    sl->topleft_partition = -1;

    top_xy = mb_xy - (h->mb_stride << MB_FIELD(sl));

    /* Wow, what a mess, why didn't they simplify the interlacing & intra
     * stuff, I can't imagine that these complex rules are worth it. */

    topleft_xy    = top_xy - 1;
    topright_xy   = top_xy + 1;
    left_xy[LBOT] = left_xy[LTOP] = mb_xy - 1;
    sl->left_block = left_block_options[0];
    if (FRAME_MBAFF(h)) {
        const int left_mb_field_flag = IS_INTERLACED(h->cur_pic.mb_type[mb_xy - 1]);
        const int curr_mb_field_flag = IS_INTERLACED(mb_type);
        if (sl->mb_y & 1) {
            if (left_mb_field_flag != curr_mb_field_flag) {
                left_xy[LBOT] = left_xy[LTOP] = mb_xy - h->mb_stride - 1;
                if (curr_mb_field_flag) {
                    left_xy[LBOT] += h->mb_stride;
                    sl->left_block  = left_block_options[3];
                } else {
                    topleft_xy += h->mb_stride;
                    /* take top left mv from the middle of the mb, as opposed
                     * to all other modes which use the bottom right partition */
                    sl->topleft_partition = 0;
                    sl->left_block        = left_block_options[1];
                }
            }
        } else {
            if (curr_mb_field_flag) {
                topleft_xy  += h->mb_stride & (((h->cur_pic.mb_type[top_xy - 1] >> 7) & 1) - 1);
                topright_xy += h->mb_stride & (((h->cur_pic.mb_type[top_xy + 1] >> 7) & 1) - 1);
                top_xy      += h->mb_stride & (((h->cur_pic.mb_type[top_xy]     >> 7) & 1) - 1);
            }
            if (left_mb_field_flag != curr_mb_field_flag) {
                if (curr_mb_field_flag) {
                    left_xy[LBOT] += h->mb_stride;
                    sl->left_block  = left_block_options[3];
                } else {
                    sl->left_block = left_block_options[2];
                }
            }
        }
    }

    sl->topleft_mb_xy    = topleft_xy;
    sl->top_mb_xy        = top_xy;
    sl->topright_mb_xy   = topright_xy;
    sl->left_mb_xy[LTOP] = left_xy[LTOP];
    sl->left_mb_xy[LBOT] = left_xy[LBOT];
    //FIXME do we need all in the context?

    sl->topleft_type    = h->cur_pic.mb_type[topleft_xy];
    sl->top_type        = h->cur_pic.mb_type[top_xy];
    sl->topright_type   = h->cur_pic.mb_type[topright_xy];
    sl->left_type[LTOP] = h->cur_pic.mb_type[left_xy[LTOP]];
    sl->left_type[LBOT] = h->cur_pic.mb_type[left_xy[LBOT]];

    if (FMO) {
        if (h->slice_table[topleft_xy] != sl->slice_num)
            sl->topleft_type = 0;
        if (h->slice_table[top_xy] != sl->slice_num)
            sl->top_type = 0;
        if (h->slice_table[left_xy[LTOP]] != sl->slice_num)
            sl->left_type[LTOP] = sl->left_type[LBOT] = 0;
    } else {
        if (h->slice_table[topleft_xy] != sl->slice_num) {
            sl->topleft_type = 0;
            if (h->slice_table[top_xy] != sl->slice_num)
                sl->top_type = 0;
            if (h->slice_table[left_xy[LTOP]] != sl->slice_num)
                sl->left_type[LTOP] = sl->left_type[LBOT] = 0;
        }
    }
    if (h->slice_table[topright_xy] != sl->slice_num)
        sl->topright_type = 0;
}