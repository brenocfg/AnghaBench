#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_5__* mfxHDL ;
struct TYPE_17__ {int NumFrameActual; int /*<<< orphan*/ * mids; } ;
typedef  TYPE_6__ mfxFrameAllocResponse ;
struct TYPE_18__ {int Type; } ;
typedef  TYPE_7__ mfxFrameAllocRequest ;
struct TYPE_16__ {int nb_surface_ptrs_in; int nb_surface_ptrs_out; TYPE_4__** surface_ptrs_out; TYPE_2__** surface_ptrs_in; } ;
struct TYPE_14__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_15__ {TYPE_3__ Data; } ;
struct TYPE_12__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_13__ {TYPE_1__ Data; } ;
typedef  TYPE_5__ QSVVPPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_ERR_UNSUPPORTED ; 
 int MFX_MEMTYPE_EXTERNAL_FRAME ; 
 int MFX_MEMTYPE_FROM_VPPIN ; 
 int MFX_MEMTYPE_FROM_VPPOUT ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 void* av_mallocz (int) ; 

__attribute__((used)) static mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    QSVVPPContext *s = pthis;
    int i;

    if (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        return MFX_ERR_UNSUPPORTED;

    if (req->Type & MFX_MEMTYPE_FROM_VPPIN) {
        resp->mids = av_mallocz(s->nb_surface_ptrs_in * sizeof(*resp->mids));
        if (!resp->mids)
            return AVERROR(ENOMEM);

        for (i = 0; i < s->nb_surface_ptrs_in; i++)
            resp->mids[i] = s->surface_ptrs_in[i]->Data.MemId;

        resp->NumFrameActual = s->nb_surface_ptrs_in;
    } else {
        resp->mids = av_mallocz(s->nb_surface_ptrs_out * sizeof(*resp->mids));
        if (!resp->mids)
            return AVERROR(ENOMEM);

        for (i = 0; i < s->nb_surface_ptrs_out; i++)
            resp->mids[i] = s->surface_ptrs_out[i]->Data.MemId;

        resp->NumFrameActual = s->nb_surface_ptrs_out;
    }

    return MFX_ERR_NONE;
}