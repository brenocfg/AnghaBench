#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mfxStatus ;
typedef  TYPE_4__* mfxMemId ;
typedef  int /*<<< orphan*/  mfxHDL ;
struct TYPE_21__ {int /*<<< orphan*/ * V; int /*<<< orphan*/ * U; int /*<<< orphan*/ * Y; int /*<<< orphan*/  Pitch; } ;
typedef  TYPE_5__ mfxFrameData ;
struct TYPE_23__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sw_format; TYPE_7__* hwctx; } ;
struct TYPE_22__ {TYPE_1__* surfaces; } ;
struct TYPE_18__ {int /*<<< orphan*/  MemId; } ;
struct TYPE_19__ {TYPE_2__ Data; int /*<<< orphan*/  Info; } ;
struct TYPE_20__ {TYPE_11__* locked_frame; TYPE_11__* hw_frame; int /*<<< orphan*/  handle; TYPE_3__ surf; TYPE_14__* hw_frames_ref; } ;
struct TYPE_17__ {int /*<<< orphan*/  Info; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/ * buf; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ QSVMid ;
typedef  TYPE_7__ AVQSVFramesContext ;
typedef  TYPE_8__ AVHWFramesContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_HWFRAME_MAP_DIRECT ; 
 int /*<<< orphan*/  AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  MFX_ERR_MEMORY_ALLOC ; 
 int /*<<< orphan*/  MFX_ERR_NONE ; 
 int /*<<< orphan*/  MFX_ERR_UNDEFINED_BEHAVIOR ; 
 int /*<<< orphan*/  av_buffer_alloc (int) ; 
 int /*<<< orphan*/  av_buffer_ref (TYPE_14__*) ; 
 void* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_11__**) ; 
 int av_hwframe_map (TYPE_11__*,TYPE_11__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mfxStatus qsv_frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    QSVMid *qsv_mid = mid;
    AVHWFramesContext *hw_frames_ctx = (AVHWFramesContext*)qsv_mid->hw_frames_ref->data;
    AVQSVFramesContext *hw_frames_hwctx = hw_frames_ctx->hwctx;
    int ret;

    if (qsv_mid->locked_frame)
        return MFX_ERR_UNDEFINED_BEHAVIOR;

    /* Allocate a system memory frame that will hold the mapped data. */
    qsv_mid->locked_frame = av_frame_alloc();
    if (!qsv_mid->locked_frame)
        return MFX_ERR_MEMORY_ALLOC;
    qsv_mid->locked_frame->format  = hw_frames_ctx->sw_format;

    /* wrap the provided handle in a hwaccel AVFrame */
    qsv_mid->hw_frame = av_frame_alloc();
    if (!qsv_mid->hw_frame)
        goto fail;

    qsv_mid->hw_frame->data[3] = (uint8_t*)&qsv_mid->surf;
    qsv_mid->hw_frame->format  = AV_PIX_FMT_QSV;

    // doesn't really matter what buffer is used here
    qsv_mid->hw_frame->buf[0]  = av_buffer_alloc(1);
    if (!qsv_mid->hw_frame->buf[0])
        goto fail;

    qsv_mid->hw_frame->width   = hw_frames_ctx->width;
    qsv_mid->hw_frame->height  = hw_frames_ctx->height;

    qsv_mid->hw_frame->hw_frames_ctx = av_buffer_ref(qsv_mid->hw_frames_ref);
    if (!qsv_mid->hw_frame->hw_frames_ctx)
        goto fail;

    qsv_mid->surf.Info = hw_frames_hwctx->surfaces[0].Info;
    qsv_mid->surf.Data.MemId = qsv_mid->handle;

    /* map the data to the system memory */
    ret = av_hwframe_map(qsv_mid->locked_frame, qsv_mid->hw_frame,
                         AV_HWFRAME_MAP_DIRECT);
    if (ret < 0)
        goto fail;

    ptr->Pitch = qsv_mid->locked_frame->linesize[0];
    ptr->Y     = qsv_mid->locked_frame->data[0];
    ptr->U     = qsv_mid->locked_frame->data[1];
    ptr->V     = qsv_mid->locked_frame->data[1] + 1;

    return MFX_ERR_NONE;
fail:
    av_frame_free(&qsv_mid->hw_frame);
    av_frame_free(&qsv_mid->locked_frame);
    return MFX_ERR_MEMORY_ALLOC;
}