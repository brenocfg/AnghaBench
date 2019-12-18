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
struct TYPE_9__ {TYPE_1__* private_ref; } ;
struct TYPE_8__ {scalar_t__ hwaccel_priv; } ;
struct TYPE_7__ {int idx; } ;
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_2__ NVDECFrame ;
typedef  TYPE_3__ FrameDecodeData ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */

int ff_nvdec_get_ref_idx(AVFrame *frame)
{
    FrameDecodeData *fdd;
    NVDECFrame *cf;

    if (!frame || !frame->private_ref)
        return -1;

    fdd = (FrameDecodeData*)frame->private_ref->data;
    cf  = (NVDECFrame*)fdd->hwaccel_priv;
    if (!cf)
        return -1;

    return cf->idx;
}