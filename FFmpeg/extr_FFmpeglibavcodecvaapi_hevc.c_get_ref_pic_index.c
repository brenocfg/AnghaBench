#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ VASurfaceID ;
struct TYPE_10__ {TYPE_8__* ReferenceFrames; } ;
typedef  TYPE_2__ VAPictureParameterBufferHEVC ;
struct TYPE_11__ {TYPE_2__ pic_param; } ;
typedef  TYPE_3__ VAAPIDecodePictureHEVC ;
struct TYPE_14__ {scalar_t__ picture_id; int pic_order_cnt; } ;
struct TYPE_13__ {TYPE_1__* ref; } ;
struct TYPE_12__ {int poc; int /*<<< orphan*/  frame; } ;
struct TYPE_9__ {TYPE_3__* hwaccel_picture_private; } ;
typedef  TYPE_4__ HEVCFrame ;
typedef  TYPE_5__ HEVCContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_8__*) ; 
 scalar_t__ VA_INVALID_ID ; 
 scalar_t__ ff_vaapi_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t get_ref_pic_index(const HEVCContext *h, const HEVCFrame *frame)
{
    VAAPIDecodePictureHEVC *pic = h->ref->hwaccel_picture_private;
    VAPictureParameterBufferHEVC *pp = &pic->pic_param;
    uint8_t i;

    if (!frame)
        return 0xff;

    for (i = 0; i < FF_ARRAY_ELEMS(pp->ReferenceFrames); i++) {
        VASurfaceID pid = pp->ReferenceFrames[i].picture_id;
        int poc = pp->ReferenceFrames[i].pic_order_cnt;
        if (pid != VA_INVALID_ID && pid == ff_vaapi_get_surface_id(frame->frame) && poc == frame->poc)
            return i;
    }

    return 0xff;
}