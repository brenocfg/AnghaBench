#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mfxStatus ;
typedef  int /*<<< orphan*/  mfxSession ;
struct TYPE_10__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  GetHDL; int /*<<< orphan*/  Unlock; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Alloc; TYPE_2__* pthis; } ;
typedef  TYPE_1__ mfxFrameAllocator ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ data; } ;
struct TYPE_13__ {int /*<<< orphan*/  device_ref; TYPE_3__* hwctx; } ;
struct TYPE_12__ {int /*<<< orphan*/  nb_surfaces; } ;
struct TYPE_11__ {int /*<<< orphan*/  nb_mids; TYPE_5__* mids_buf; int /*<<< orphan*/ * mids; TYPE_6__* hw_frames_ctx; int /*<<< orphan*/ * logctx; } ;
typedef  int /*<<< orphan*/  QSVMid ;
typedef  TYPE_2__ QSVFramesContext ;
typedef  TYPE_3__ AVQSVFramesContext ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MFXVideoCORE_SetFrameAllocator (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ MFX_ERR_NONE ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 int ff_qsv_init_session_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int ff_qsv_print_error (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 TYPE_5__* qsv_create_mids (TYPE_6__*) ; 
 int /*<<< orphan*/  qsv_frame_alloc ; 
 int /*<<< orphan*/  qsv_frame_free ; 
 int /*<<< orphan*/  qsv_frame_get_hdl ; 
 int /*<<< orphan*/  qsv_frame_lock ; 
 int /*<<< orphan*/  qsv_frame_unlock ; 

int ff_qsv_init_session_frames(AVCodecContext *avctx, mfxSession *psession,
                               QSVFramesContext *qsv_frames_ctx,
                               const char *load_plugins, int opaque, int gpu_copy)
{
    mfxFrameAllocator frame_allocator = {
        .pthis  = qsv_frames_ctx,
        .Alloc  = qsv_frame_alloc,
        .Lock   = qsv_frame_lock,
        .Unlock = qsv_frame_unlock,
        .GetHDL = qsv_frame_get_hdl,
        .Free   = qsv_frame_free,
    };

    AVHWFramesContext    *frames_ctx = (AVHWFramesContext*)qsv_frames_ctx->hw_frames_ctx->data;
    AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;

    mfxSession    session;
    mfxStatus err;

    int ret;

    ret = ff_qsv_init_session_device(avctx, &session,
                                     frames_ctx->device_ref, load_plugins, gpu_copy);
    if (ret < 0)
        return ret;

    if (!opaque) {
        qsv_frames_ctx->logctx = avctx;

        /* allocate the memory ids for the external frames */
        av_buffer_unref(&qsv_frames_ctx->mids_buf);
        qsv_frames_ctx->mids_buf = qsv_create_mids(qsv_frames_ctx->hw_frames_ctx);
        if (!qsv_frames_ctx->mids_buf)
            return AVERROR(ENOMEM);
        qsv_frames_ctx->mids    = (QSVMid*)qsv_frames_ctx->mids_buf->data;
        qsv_frames_ctx->nb_mids = frames_hwctx->nb_surfaces;

        err = MFXVideoCORE_SetFrameAllocator(session, &frame_allocator);
        if (err != MFX_ERR_NONE)
            return ff_qsv_print_error(avctx, err,
                                      "Error setting a frame allocator");
    }

    *psession = session;
    return 0;
}