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
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_1__* mfxHDL ;
struct TYPE_10__ {int /*<<< orphan*/  NumFrameActual; int /*<<< orphan*/  mids; } ;
typedef  TYPE_2__ mfxFrameAllocResponse ;
struct TYPE_11__ {int Type; } ;
typedef  TYPE_3__ mfxFrameAllocRequest ;
struct TYPE_12__ {int /*<<< orphan*/  nb_mem_ids; int /*<<< orphan*/  mem_ids; } ;
struct TYPE_9__ {TYPE_4__* priv; } ;
typedef  TYPE_4__ QSVDeintContext ;
typedef  TYPE_1__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_ERR_UNSUPPORTED ; 
 int MFX_MEMTYPE_EXTERNAL_FRAME ; 
 int MFX_MEMTYPE_FROM_VPPIN ; 
 int MFX_MEMTYPE_FROM_VPPOUT ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 

__attribute__((used)) static mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVFilterContext *ctx = pthis;
    QSVDeintContext   *s = ctx->priv;

    if (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        return MFX_ERR_UNSUPPORTED;

    resp->mids           = s->mem_ids;
    resp->NumFrameActual = s->nb_mem_ids;

    return MFX_ERR_NONE;
}