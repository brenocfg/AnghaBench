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
struct TYPE_6__ {int* mb_type; } ;
struct TYPE_8__ {int mb_stride; scalar_t__* slice_table; TYPE_1__ cur_pic; } ;
struct TYPE_7__ {int mb_x; int mb_y; scalar_t__ slice_num; int mb_mbaff; int mb_field_decoding_flag; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */
 scalar_t__ IS_INTERLACED (int) ; 

__attribute__((used)) static void predict_field_decoding_flag(const H264Context *h, H264SliceContext *sl)
{
    const int mb_xy = sl->mb_x + sl->mb_y * h->mb_stride;
    int mb_type     = (h->slice_table[mb_xy - 1] == sl->slice_num) ?
                      h->cur_pic.mb_type[mb_xy - 1] :
                      (h->slice_table[mb_xy - h->mb_stride] == sl->slice_num) ?
                      h->cur_pic.mb_type[mb_xy - h->mb_stride] : 0;
    sl->mb_mbaff    = sl->mb_field_decoding_flag = IS_INTERLACED(mb_type) ? 1 : 0;
}