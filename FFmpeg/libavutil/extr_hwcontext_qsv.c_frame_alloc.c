#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_3__* mfxHDL ;
struct TYPE_17__ {scalar_t__ Width; scalar_t__ Height; scalar_t__ FourCC; scalar_t__ ChromaFormat; } ;
typedef  TYPE_4__ mfxFrameInfo ;
struct TYPE_18__ {int /*<<< orphan*/  NumFrameActual; int /*<<< orphan*/  mids; } ;
typedef  TYPE_5__ mfxFrameAllocResponse ;
struct TYPE_19__ {int Type; TYPE_4__ Info; } ;
typedef  TYPE_6__ mfxFrameAllocRequest ;
struct TYPE_21__ {int /*<<< orphan*/  nb_surfaces; TYPE_2__* surfaces; } ;
struct TYPE_20__ {int /*<<< orphan*/  mem_ids; } ;
struct TYPE_16__ {TYPE_8__* hwctx; TYPE_1__* internal; } ;
struct TYPE_15__ {TYPE_4__ Info; } ;
struct TYPE_14__ {TYPE_7__* priv; } ;
typedef  TYPE_7__ QSVFramesContext ;
typedef  TYPE_8__ AVQSVFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_ERR_UNSUPPORTED ; 
 int MFX_MEMTYPE_EXTERNAL_FRAME ; 
 int MFX_MEMTYPE_FROM_VPPIN ; 
 int MFX_MEMTYPE_FROM_VPPOUT ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->internal->priv;
    AVQSVFramesContext *hwctx = ctx->hwctx;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = &hwctx->surfaces[0].Info;

    if (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        return MFX_ERR_UNSUPPORTED;
    if (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        return MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->NumFrameActual = hwctx->nb_surfaces;

    return MFX_ERR_NONE;
}