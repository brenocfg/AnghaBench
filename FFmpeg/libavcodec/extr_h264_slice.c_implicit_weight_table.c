#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  long long int64_t ;
struct TYPE_15__ {int picture_structure; TYPE_1__* cur_pic_ptr; } ;
struct TYPE_13__ {int use_weight; int use_weight_chroma; int luma_log2_weight_denom; int chroma_log2_weight_denom; int*** implicit_weight; scalar_t__* chroma_weight_flag; scalar_t__* luma_weight_flag; } ;
struct TYPE_14__ {int* ref_count; TYPE_4__ pwt; TYPE_3__** ref_list; } ;
struct TYPE_12__ {long long poc; TYPE_2__* parent; } ;
struct TYPE_11__ {int /*<<< orphan*/  long_ref; } ;
struct TYPE_10__ {int poc; int* field_poc; } ;
typedef  TYPE_5__ H264SliceContext ;
typedef  TYPE_6__ H264Context ;

/* Variables and functions */
 int FFABS (int) ; 
 int /*<<< orphan*/  FRAME_MBAFF (TYPE_6__ const*) ; 
 int PICT_FRAME ; 
 int av_clip_int8 (long long) ; 

__attribute__((used)) static void implicit_weight_table(const H264Context *h, H264SliceContext *sl, int field)
{
    int ref0, ref1, i, cur_poc, ref_start, ref_count0, ref_count1;

    for (i = 0; i < 2; i++) {
        sl->pwt.luma_weight_flag[i]   = 0;
        sl->pwt.chroma_weight_flag[i] = 0;
    }

    if (field < 0) {
        if (h->picture_structure == PICT_FRAME) {
            cur_poc = h->cur_pic_ptr->poc;
        } else {
            cur_poc = h->cur_pic_ptr->field_poc[h->picture_structure - 1];
        }
        if (sl->ref_count[0] == 1 && sl->ref_count[1] == 1 && !FRAME_MBAFF(h) &&
            sl->ref_list[0][0].poc + (int64_t)sl->ref_list[1][0].poc == 2LL * cur_poc) {
            sl->pwt.use_weight        = 0;
            sl->pwt.use_weight_chroma = 0;
            return;
        }
        ref_start  = 0;
        ref_count0 = sl->ref_count[0];
        ref_count1 = sl->ref_count[1];
    } else {
        cur_poc    = h->cur_pic_ptr->field_poc[field];
        ref_start  = 16;
        ref_count0 = 16 + 2 * sl->ref_count[0];
        ref_count1 = 16 + 2 * sl->ref_count[1];
    }

    sl->pwt.use_weight               = 2;
    sl->pwt.use_weight_chroma        = 2;
    sl->pwt.luma_log2_weight_denom   = 5;
    sl->pwt.chroma_log2_weight_denom = 5;

    for (ref0 = ref_start; ref0 < ref_count0; ref0++) {
        int64_t poc0 = sl->ref_list[0][ref0].poc;
        for (ref1 = ref_start; ref1 < ref_count1; ref1++) {
            int w = 32;
            if (!sl->ref_list[0][ref0].parent->long_ref && !sl->ref_list[1][ref1].parent->long_ref) {
                int poc1 = sl->ref_list[1][ref1].poc;
                int td   = av_clip_int8(poc1 - poc0);
                if (td) {
                    int tb = av_clip_int8(cur_poc - poc0);
                    int tx = (16384 + (FFABS(td) >> 1)) / td;
                    int dist_scale_factor = (tb * tx + 32) >> 8;
                    if (dist_scale_factor >= -64 && dist_scale_factor <= 128)
                        w = 64 - dist_scale_factor;
                }
            }
            if (field < 0) {
                sl->pwt.implicit_weight[ref0][ref1][0] =
                sl->pwt.implicit_weight[ref0][ref1][1] = w;
            } else {
                sl->pwt.implicit_weight[ref0][ref1][field] = w;
            }
        }
    }
}