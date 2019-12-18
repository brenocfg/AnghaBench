#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int IOPattern; int AsyncDepth; int /*<<< orphan*/  NumExtParam; int /*<<< orphan*/  ExtParam; } ;
typedef  TYPE_1__ mfxVideoParam ;
typedef  int /*<<< orphan*/ * mfxSession ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_22__ {scalar_t__ data; } ;
struct TYPE_21__ {int pix_fmt; int /*<<< orphan*/  hw_device_ctx; TYPE_9__* hw_frames_ctx; TYPE_4__* hwaccel_context; } ;
struct TYPE_20__ {TYPE_3__* hwctx; } ;
struct TYPE_19__ {int iopattern; int /*<<< orphan*/  nb_ext_buffers; int /*<<< orphan*/  ext_buffers; int /*<<< orphan*/ * session; } ;
struct TYPE_18__ {int frame_type; } ;
struct TYPE_17__ {int orig_pix_fmt; int async_depth; int iopattern; int /*<<< orphan*/  nb_ext_buffers; int /*<<< orphan*/  ext_buffers; scalar_t__ async_fifo; } ;
typedef  TYPE_2__ QSVContext ;
typedef  TYPE_3__ AVQSVFramesContext ;
typedef  TYPE_4__ AVQSVContext ;
typedef  TYPE_5__ AVHWFramesContext ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_OUT_SYSTEM_MEMORY ; 
 int MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 scalar_t__ av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_format (TYPE_6__*,int*) ; 
 int /*<<< orphan*/  ff_qsv_print_iopattern (TYPE_6__*,int,char*) ; 
 int qsv_fifo_item_size () ; 
 int qsv_init_session (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qsv_decode_preinit(AVCodecContext *avctx, QSVContext *q, enum AVPixelFormat pix_fmt, mfxVideoParam *param)
{
    mfxSession session = NULL;
    int iopattern = 0;
    int ret;
    enum AVPixelFormat pix_fmts[3] = {
        AV_PIX_FMT_QSV, /* opaque format in case of video memory output */
        pix_fmt,        /* system memory format obtained from bitstream parser */
        AV_PIX_FMT_NONE };

    ret = ff_get_format(avctx, pix_fmts);
    if (ret < 0) {
        q->orig_pix_fmt = avctx->pix_fmt = AV_PIX_FMT_NONE;
        return ret;
    }

    if (!q->async_fifo) {
        q->async_fifo = av_fifo_alloc(q->async_depth * qsv_fifo_item_size());
        if (!q->async_fifo)
            return AVERROR(ENOMEM);
    }

    if (avctx->pix_fmt == AV_PIX_FMT_QSV && avctx->hwaccel_context) {
        AVQSVContext *user_ctx = avctx->hwaccel_context;
        session           = user_ctx->session;
        iopattern         = user_ctx->iopattern;
        q->ext_buffers    = user_ctx->ext_buffers;
        q->nb_ext_buffers = user_ctx->nb_ext_buffers;
    }

    if (avctx->hw_frames_ctx) {
        AVHWFramesContext    *frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
        AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;

        if (!iopattern) {
            if (frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)
                iopattern = MFX_IOPATTERN_OUT_OPAQUE_MEMORY;
            else if (frames_hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                iopattern = MFX_IOPATTERN_OUT_VIDEO_MEMORY;
        }
    }

    if (!iopattern)
        iopattern = MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
    q->iopattern = iopattern;

    ff_qsv_print_iopattern(avctx, q->iopattern, "Decoder");

    ret = qsv_init_session(avctx, q, session, avctx->hw_frames_ctx, avctx->hw_device_ctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error initializing an MFX session\n");
        return ret;
    }

    param->IOPattern   = q->iopattern;
    param->AsyncDepth  = q->async_depth;
    param->ExtParam    = q->ext_buffers;
    param->NumExtParam = q->nb_ext_buffers;

    return 0;
 }