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
struct TYPE_5__ {scalar_t__ TopFieldOrderCnt; scalar_t__ BottomFieldOrderCnt; int /*<<< orphan*/  flags; int /*<<< orphan*/  frame_idx; int /*<<< orphan*/  picture_id; } ;
typedef  TYPE_1__ VAPictureH264 ;
struct TYPE_6__ {int reference; scalar_t__* field_poc; scalar_t__ long_ref; int /*<<< orphan*/  frame_num; int /*<<< orphan*/  pic_id; int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ H264Picture ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 int PICT_FRAME ; 
 int PICT_TOP_FIELD ; 
 int /*<<< orphan*/  VA_PICTURE_H264_BOTTOM_FIELD ; 
 int /*<<< orphan*/  VA_PICTURE_H264_LONG_TERM_REFERENCE ; 
 int /*<<< orphan*/  VA_PICTURE_H264_SHORT_TERM_REFERENCE ; 
 int /*<<< orphan*/  VA_PICTURE_H264_TOP_FIELD ; 
 int /*<<< orphan*/  ff_vaapi_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fill_vaapi_pic(VAPictureH264 *va_pic,
                           const H264Picture *pic,
                           int            pic_structure)
{
    if (pic_structure == 0)
        pic_structure = pic->reference;
    pic_structure &= PICT_FRAME; /* PICT_TOP_FIELD|PICT_BOTTOM_FIELD */

    va_pic->picture_id = ff_vaapi_get_surface_id(pic->f);
    va_pic->frame_idx  = pic->long_ref ? pic->pic_id : pic->frame_num;

    va_pic->flags      = 0;
    if (pic_structure != PICT_FRAME)
        va_pic->flags |= (pic_structure & PICT_TOP_FIELD) ? VA_PICTURE_H264_TOP_FIELD : VA_PICTURE_H264_BOTTOM_FIELD;
    if (pic->reference)
        va_pic->flags |= pic->long_ref ? VA_PICTURE_H264_LONG_TERM_REFERENCE : VA_PICTURE_H264_SHORT_TERM_REFERENCE;

    va_pic->TopFieldOrderCnt = 0;
    if (pic->field_poc[0] != INT_MAX)
        va_pic->TopFieldOrderCnt = pic->field_poc[0];

    va_pic->BottomFieldOrderCnt = 0;
    if (pic->field_poc[1] != INT_MAX)
        va_pic->BottomFieldOrderCnt = pic->field_poc[1];
}