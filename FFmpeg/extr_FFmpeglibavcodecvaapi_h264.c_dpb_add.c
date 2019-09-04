#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ picture_id; int flags; int /*<<< orphan*/  BottomFieldOrderCnt; int /*<<< orphan*/  TopFieldOrderCnt; } ;
typedef  TYPE_1__ VAPictureH264 ;
struct TYPE_10__ {int size; int max_size; TYPE_1__* va_pics; } ;
struct TYPE_9__ {int /*<<< orphan*/  f; } ;
typedef  TYPE_2__ H264Picture ;
typedef  TYPE_3__ DPB ;

/* Variables and functions */
 int VA_PICTURE_H264_BOTTOM_FIELD ; 
 int VA_PICTURE_H264_TOP_FIELD ; 
 scalar_t__ ff_vaapi_get_surface_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_vaapi_pic (TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpb_add(DPB *dpb, const H264Picture *pic)
{
    int i;

    if (dpb->size >= dpb->max_size)
        return -1;

    for (i = 0; i < dpb->size; i++) {
        VAPictureH264 * const va_pic = &dpb->va_pics[i];
        if (va_pic->picture_id == ff_vaapi_get_surface_id(pic->f)) {
            VAPictureH264 temp_va_pic;
            fill_vaapi_pic(&temp_va_pic, pic, 0);

            if ((temp_va_pic.flags ^ va_pic->flags) & (VA_PICTURE_H264_TOP_FIELD | VA_PICTURE_H264_BOTTOM_FIELD)) {
                va_pic->flags |= temp_va_pic.flags & (VA_PICTURE_H264_TOP_FIELD | VA_PICTURE_H264_BOTTOM_FIELD);
                /* Merge second field */
                if (temp_va_pic.flags & VA_PICTURE_H264_TOP_FIELD) {
                    va_pic->TopFieldOrderCnt    = temp_va_pic.TopFieldOrderCnt;
                } else {
                    va_pic->BottomFieldOrderCnt = temp_va_pic.BottomFieldOrderCnt;
                }
            }
            return 0;
        }
    }

    fill_vaapi_pic(&dpb->va_pics[dpb->size++], pic, 0);
    return 0;
}