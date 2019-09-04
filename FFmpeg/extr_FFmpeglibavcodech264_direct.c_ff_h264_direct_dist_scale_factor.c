#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ picture_structure; TYPE_1__* cur_pic_ptr; } ;
struct TYPE_14__ {int* ref_count; void** dist_scale_factor; void*** dist_scale_factor_field; TYPE_3__** ref_list; } ;
struct TYPE_13__ {int poc; TYPE_2__* parent; } ;
struct TYPE_12__ {int* field_poc; } ;
struct TYPE_11__ {int* field_poc; int poc; } ;
typedef  TYPE_4__ H264SliceContext ;
typedef  TYPE_5__ H264Context ;

/* Variables and functions */
 scalar_t__ FIELD_PICTURE (TYPE_5__ const* const) ; 
 scalar_t__ FRAME_MBAFF (TYPE_5__ const* const) ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 void* get_scale_factor (TYPE_4__*,int const,int const,int) ; 

void ff_h264_direct_dist_scale_factor(const H264Context *const h,
                                      H264SliceContext *sl)
{
    const int poc  = FIELD_PICTURE(h) ? h->cur_pic_ptr->field_poc[h->picture_structure == PICT_BOTTOM_FIELD]
                                      : h->cur_pic_ptr->poc;
    const int poc1 = sl->ref_list[1][0].poc;
    int i, field;

    if (FRAME_MBAFF(h))
        for (field = 0; field < 2; field++) {
            const int poc  = h->cur_pic_ptr->field_poc[field];
            const int poc1 = sl->ref_list[1][0].parent->field_poc[field];
            for (i = 0; i < 2 * sl->ref_count[0]; i++)
                sl->dist_scale_factor_field[field][i ^ field] =
                    get_scale_factor(sl, poc, poc1, i + 16);
        }

    for (i = 0; i < sl->ref_count[0]; i++)
        sl->dist_scale_factor[i] = get_scale_factor(sl, poc, poc1, i);
}