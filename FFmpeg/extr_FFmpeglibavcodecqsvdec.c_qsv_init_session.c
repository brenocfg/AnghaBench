#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * mfxSession ;
struct TYPE_5__ {int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_4__ {scalar_t__ iopattern; int /*<<< orphan*/ * session; int /*<<< orphan*/ * internal_session; int /*<<< orphan*/  load_plugins; TYPE_3__ frames_ctx; } ;
typedef  TYPE_1__ QSVContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MFXClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MFXVideoDECODE_Close (int /*<<< orphan*/ *) ; 
 scalar_t__ MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int ff_qsv_init_internal_session (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ff_qsv_init_session_device (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_qsv_init_session_frames (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qsv_init_session(AVCodecContext *avctx, QSVContext *q, mfxSession session,
                            AVBufferRef *hw_frames_ref, AVBufferRef *hw_device_ref)
{
    int ret;

    if (session) {
        q->session = session;
    } else if (hw_frames_ref) {
        if (q->internal_session) {
            MFXClose(q->internal_session);
            q->internal_session = NULL;
        }
        av_buffer_unref(&q->frames_ctx.hw_frames_ctx);

        q->frames_ctx.hw_frames_ctx = av_buffer_ref(hw_frames_ref);
        if (!q->frames_ctx.hw_frames_ctx)
            return AVERROR(ENOMEM);

        ret = ff_qsv_init_session_frames(avctx, &q->internal_session,
                                         &q->frames_ctx, q->load_plugins,
                                         q->iopattern == MFX_IOPATTERN_OUT_OPAQUE_MEMORY);
        if (ret < 0) {
            av_buffer_unref(&q->frames_ctx.hw_frames_ctx);
            return ret;
        }

        q->session = q->internal_session;
    } else if (hw_device_ref) {
        if (q->internal_session) {
            MFXClose(q->internal_session);
            q->internal_session = NULL;
        }

        ret = ff_qsv_init_session_device(avctx, &q->internal_session,
                                         hw_device_ref, q->load_plugins);
        if (ret < 0)
            return ret;

        q->session = q->internal_session;
    } else {
        if (!q->internal_session) {
            ret = ff_qsv_init_internal_session(avctx, &q->internal_session,
                                               q->load_plugins);
            if (ret < 0)
                return ret;
        }

        q->session = q->internal_session;
    }

    /* make sure the decoder is uninitialized */
    MFXVideoDECODE_Close(q->session);

    return 0;
}