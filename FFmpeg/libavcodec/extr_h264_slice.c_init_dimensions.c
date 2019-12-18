#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sps; } ;
struct TYPE_9__ {int width; int height; int width_from_caller; int height_from_caller; int crop_right; int crop_left; int crop_top; int crop_bottom; TYPE_2__* avctx; TYPE_1__ ps; } ;
struct TYPE_8__ {int crop_right; int crop_left; int crop_top; int crop_bottom; } ;
struct TYPE_7__ {int coded_width; int coded_height; int width; int height; } ;
typedef  TYPE_3__ SPS ;
typedef  TYPE_4__ H264Context ;

/* Variables and functions */
 scalar_t__ FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int init_dimensions(H264Context *h)
{
    const SPS *sps = (const SPS*)h->ps.sps;
    int cr = sps->crop_right;
    int cl = sps->crop_left;
    int ct = sps->crop_top;
    int cb = sps->crop_bottom;
    int width  = h->width  - (cr + cl);
    int height = h->height - (ct + cb);
    av_assert0(sps->crop_right + sps->crop_left < (unsigned)h->width);
    av_assert0(sps->crop_top + sps->crop_bottom < (unsigned)h->height);

    /* handle container cropping */
    if (h->width_from_caller > 0 && h->height_from_caller > 0     &&
        !sps->crop_top && !sps->crop_left                         &&
        FFALIGN(h->width_from_caller,  16) == FFALIGN(width,  16) &&
        FFALIGN(h->height_from_caller, 16) == FFALIGN(height, 16) &&
        h->width_from_caller  <= width &&
        h->height_from_caller <= height) {
        width  = h->width_from_caller;
        height = h->height_from_caller;
        cl = 0;
        ct = 0;
        cr = h->width - width;
        cb = h->height - height;
    } else {
        h->width_from_caller  = 0;
        h->height_from_caller = 0;
    }

    h->avctx->coded_width  = h->width;
    h->avctx->coded_height = h->height;
    h->avctx->width        = width;
    h->avctx->height       = height;
    h->crop_right          = cr;
    h->crop_left           = cl;
    h->crop_top            = ct;
    h->crop_bottom         = cb;

    return 0;
}