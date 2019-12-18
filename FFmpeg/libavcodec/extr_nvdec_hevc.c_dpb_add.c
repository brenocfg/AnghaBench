#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* RefPicIdx; int* IsLongTerm; int /*<<< orphan*/ * PicOrderCntVal; } ;
struct TYPE_13__ {TYPE_3__* hwaccel_priv; } ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  poc; TYPE_2__* frame; } ;
struct TYPE_11__ {int idx; } ;
struct TYPE_10__ {TYPE_1__* private_ref; } ;
struct TYPE_9__ {scalar_t__ data; } ;
typedef  TYPE_3__ NVDECFrame ;
typedef  TYPE_4__ HEVCFrame ;
typedef  TYPE_5__ FrameDecodeData ;
typedef  TYPE_6__ CUVIDHEVCPICPARAMS ;

/* Variables and functions */
 int HEVC_FRAME_FLAG_LONG_REF ; 

__attribute__((used)) static void dpb_add(CUVIDHEVCPICPARAMS *pp, int idx, const HEVCFrame *src)
{
    FrameDecodeData *fdd = (FrameDecodeData*)src->frame->private_ref->data;
    const NVDECFrame *cf = fdd->hwaccel_priv;

    pp->RefPicIdx[idx]      = cf ? cf->idx : -1;
    pp->PicOrderCntVal[idx] = src->poc;
    pp->IsLongTerm[idx]     = !!(src->flags & HEVC_FRAME_FLAG_LONG_REF);
}