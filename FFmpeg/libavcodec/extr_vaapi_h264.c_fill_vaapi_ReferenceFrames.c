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
struct TYPE_9__ {int /*<<< orphan*/ * ReferenceFrames; } ;
typedef  TYPE_1__ VAPictureParameterBufferH264 ;
struct TYPE_12__ {int max_size; int /*<<< orphan*/ * va_pics; scalar_t__ size; } ;
struct TYPE_11__ {int short_ref_count; TYPE_2__** long_ref; TYPE_2__** short_ref; } ;
struct TYPE_10__ {scalar_t__ reference; } ;
typedef  TYPE_2__ H264Picture ;
typedef  TYPE_3__ H264Context ;
typedef  TYPE_4__ DPB ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ *) ; 
 scalar_t__ dpb_add (TYPE_4__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  init_vaapi_pic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_vaapi_ReferenceFrames(VAPictureParameterBufferH264 *pic_param,
                                      const H264Context            *h)
{
    DPB dpb;
    int i;

    dpb.size     = 0;
    dpb.max_size = FF_ARRAY_ELEMS(pic_param->ReferenceFrames);
    dpb.va_pics  = pic_param->ReferenceFrames;
    for (i = 0; i < dpb.max_size; i++)
        init_vaapi_pic(&dpb.va_pics[i]);

    for (i = 0; i < h->short_ref_count; i++) {
        const H264Picture *pic = h->short_ref[i];
        if (pic && pic->reference && dpb_add(&dpb, pic) < 0)
            return -1;
    }

    for (i = 0; i < 16; i++) {
        const H264Picture *pic = h->long_ref[i];
        if (pic && pic->reference && dpb_add(&dpb, pic) < 0)
            return -1;
    }
    return 0;
}