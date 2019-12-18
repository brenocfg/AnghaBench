#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_2__* mfxHDL ;
struct TYPE_20__ {scalar_t__ Width; scalar_t__ Height; scalar_t__ FourCC; scalar_t__ ChromaFormat; } ;
typedef  TYPE_3__ mfxFrameInfo ;
typedef  int /*<<< orphan*/  mfxFrameAllocResponse ;
struct TYPE_21__ {int Type; int /*<<< orphan*/  NumFrameSuggested; TYPE_3__ Info; } ;
typedef  TYPE_4__ mfxFrameAllocRequest ;
struct TYPE_24__ {scalar_t__ data; } ;
struct TYPE_23__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  initial_pool_size; int /*<<< orphan*/  sw_format; int /*<<< orphan*/  format; TYPE_6__* hwctx; int /*<<< orphan*/  device_ref; } ;
struct TYPE_22__ {int frame_type; TYPE_1__* surfaces; } ;
struct TYPE_19__ {int /*<<< orphan*/  logctx; TYPE_8__* hw_frames_ctx; TYPE_8__* mids_buf; } ;
struct TYPE_18__ {TYPE_3__ Info; } ;
typedef  TYPE_2__ QSVFramesContext ;
typedef  TYPE_6__ AVQSVFramesContext ;
typedef  TYPE_7__ AVHWFramesContext ;
typedef  TYPE_8__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  MFX_ERR_MEMORY_ALLOC ; 
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_ERR_UNSUPPORTED ; 
 int MFX_MEMTYPE_EXTERNAL_FRAME ; 
 int MFX_MEMTYPE_FROM_DECODE ; 
 int MFX_MEMTYPE_FROM_ENCODE ; 
 int MFX_MEMTYPE_INTERNAL_FRAME ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_8__**) ; 
 TYPE_8__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 int av_hwframe_ctx_init (TYPE_8__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_qsv_map_fourcc (scalar_t__) ; 
 TYPE_8__* qsv_create_mids (TYPE_8__*) ; 
 int qsv_setup_mids (int /*<<< orphan*/ *,TYPE_8__*,TYPE_8__*) ; 

__attribute__((used)) static mfxStatus qsv_frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                                 mfxFrameAllocResponse *resp)
{
    QSVFramesContext *ctx = pthis;
    int ret;

    /* this should only be called from an encoder or decoder and
     * only allocates video memory frames */
    if (!(req->Type & (MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET |
                       MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET))         ||
        !(req->Type & (MFX_MEMTYPE_FROM_DECODE | MFX_MEMTYPE_FROM_ENCODE)))
        return MFX_ERR_UNSUPPORTED;

    if (req->Type & MFX_MEMTYPE_EXTERNAL_FRAME) {
        /* external frames -- fill from the caller-supplied frames context */
        AVHWFramesContext *frames_ctx = (AVHWFramesContext*)ctx->hw_frames_ctx->data;
        AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;
        mfxFrameInfo      *i  = &req->Info;
        mfxFrameInfo      *i1 = &frames_hwctx->surfaces[0].Info;

        if (i->Width  > i1->Width  || i->Height > i1->Height ||
            i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
            av_log(ctx->logctx, AV_LOG_ERROR, "Mismatching surface properties in an "
                   "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
                   i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
                   i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
            return MFX_ERR_UNSUPPORTED;
        }

        ret = qsv_setup_mids(resp, ctx->hw_frames_ctx, ctx->mids_buf);
        if (ret < 0) {
            av_log(ctx->logctx, AV_LOG_ERROR,
                   "Error filling an external frame allocation request\n");
            return MFX_ERR_MEMORY_ALLOC;
        }
    } else if (req->Type & MFX_MEMTYPE_INTERNAL_FRAME) {
        /* internal frames -- allocate a new hw frames context */
        AVHWFramesContext *ext_frames_ctx = (AVHWFramesContext*)ctx->hw_frames_ctx->data;
        mfxFrameInfo      *i  = &req->Info;

        AVBufferRef *frames_ref, *mids_buf;
        AVHWFramesContext *frames_ctx;
        AVQSVFramesContext *frames_hwctx;

        frames_ref = av_hwframe_ctx_alloc(ext_frames_ctx->device_ref);
        if (!frames_ref)
            return MFX_ERR_MEMORY_ALLOC;

        frames_ctx   = (AVHWFramesContext*)frames_ref->data;
        frames_hwctx = frames_ctx->hwctx;

        frames_ctx->format            = AV_PIX_FMT_QSV;
        frames_ctx->sw_format         = ff_qsv_map_fourcc(i->FourCC);
        frames_ctx->width             = i->Width;
        frames_ctx->height            = i->Height;
        frames_ctx->initial_pool_size = req->NumFrameSuggested;

        frames_hwctx->frame_type      = req->Type;

        ret = av_hwframe_ctx_init(frames_ref);
        if (ret < 0) {
            av_log(ctx->logctx, AV_LOG_ERROR,
                   "Error initializing a frames context for an internal frame "
                   "allocation request\n");
            av_buffer_unref(&frames_ref);
            return MFX_ERR_MEMORY_ALLOC;
        }

        mids_buf = qsv_create_mids(frames_ref);
        if (!mids_buf) {
            av_buffer_unref(&frames_ref);
            return MFX_ERR_MEMORY_ALLOC;
        }

        ret = qsv_setup_mids(resp, frames_ref, mids_buf);
        av_buffer_unref(&mids_buf);
        av_buffer_unref(&frames_ref);
        if (ret < 0) {
            av_log(ctx->logctx, AV_LOG_ERROR,
                   "Error filling an internal frame allocation request\n");
            return MFX_ERR_MEMORY_ALLOC;
        }
    } else {
        return MFX_ERR_UNSUPPORTED;
    }

    return MFX_ERR_NONE;
}