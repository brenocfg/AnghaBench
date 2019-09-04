#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  pic_order_cnt; int /*<<< orphan*/  picture_id; } ;
typedef  TYPE_1__ VAPictureHEVC ;
struct TYPE_8__ {int /*<<< orphan*/  top_field_first; scalar_t__ interlaced_frame; } ;
struct TYPE_7__ {int flags; TYPE_5__* frame; int /*<<< orphan*/  poc; } ;
typedef  TYPE_2__ HEVCFrame ;

/* Variables and functions */
 int HEVC_FRAME_FLAG_LONG_REF ; 
 int VA_PICTURE_HEVC_BOTTOM_FIELD ; 
 int VA_PICTURE_HEVC_FIELD_PIC ; 
 int VA_PICTURE_HEVC_LONG_TERM_REFERENCE ; 
 int /*<<< orphan*/  ff_vaapi_get_surface_id (TYPE_5__*) ; 

__attribute__((used)) static void fill_vaapi_pic(VAPictureHEVC *va_pic, const HEVCFrame *pic, int rps_type)
{
    va_pic->picture_id    = ff_vaapi_get_surface_id(pic->frame);
    va_pic->pic_order_cnt = pic->poc;
    va_pic->flags         = rps_type;

    if (pic->flags & HEVC_FRAME_FLAG_LONG_REF)
        va_pic->flags |= VA_PICTURE_HEVC_LONG_TERM_REFERENCE;

    if (pic->frame->interlaced_frame) {
        va_pic->flags |= VA_PICTURE_HEVC_FIELD_PIC;

        if (!pic->frame->top_field_first)
            va_pic->flags |= VA_PICTURE_HEVC_BOTTOM_FIELD;
    }
}