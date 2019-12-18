#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_27__ ;
typedef  struct TYPE_32__   TYPE_25__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {int codec_id; TYPE_4__* hwaccel_context; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_37__ {TYPE_3__* hwctx; } ;
struct TYPE_36__ {int iopattern; int opaque_alloc; int nb_ext_buffers; TYPE_25__** ext_buffers; } ;
struct TYPE_35__ {int frame_type; } ;
struct TYPE_33__ {int AsyncDepth; int IOPattern; int NumExtParam; TYPE_25__** ExtParam; } ;
struct TYPE_34__ {int async_depth; int nb_extparam_internal; TYPE_6__* avctx; TYPE_27__ param; int /*<<< orphan*/  session; int /*<<< orphan*/  req; TYPE_25__** extparam_internal; TYPE_25__** extparam; int /*<<< orphan*/  ver; int /*<<< orphan*/  async_fifo; } ;
struct TYPE_32__ {scalar_t__ BufferId; } ;
struct TYPE_31__ {scalar_t__ data; } ;
typedef  TYPE_2__ QSVEncContext ;
typedef  TYPE_3__ AVQSVFramesContext ;
typedef  TYPE_4__ AVQSVContext ;
typedef  TYPE_5__ AVHWFramesContext ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_CODEC_ID_MJPEG 129 
#define  AV_CODEC_ID_VP9 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MFXQueryVersion (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MFXVideoENCODE_Init (int /*<<< orphan*/ ,TYPE_27__*) ; 
 int MFXVideoENCODE_Query (int /*<<< orphan*/ ,TYPE_27__*,TYPE_27__*) ; 
 int MFXVideoENCODE_QueryIOSurf (int /*<<< orphan*/ ,TYPE_27__*,int /*<<< orphan*/ *) ; 
 int MFX_IOPATTERN_IN_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_IN_SYSTEM_MEMORY ; 
 int MFX_IOPATTERN_IN_VIDEO_MEMORY ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET ; 
 int MFX_WRN_PARTIAL_ACCELERATION ; 
 int /*<<< orphan*/  av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_25__** av_mallocz_array (int,int) ; 
 int ff_qsv_print_error (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  ff_qsv_print_warning (TYPE_6__*,int,char*) ; 
 int init_video_param (TYPE_6__*,TYPE_2__*) ; 
 int init_video_param_jpeg (TYPE_6__*,TYPE_2__*) ; 
 int qsv_fifo_item_size () ; 
 int qsv_init_opaque_alloc (TYPE_6__*,TYPE_2__*) ; 
 int qsv_retrieve_enc_jpeg_params (TYPE_6__*,TYPE_2__*) ; 
 int qsv_retrieve_enc_params (TYPE_6__*,TYPE_2__*) ; 
 int qsv_retrieve_enc_vp9_params (TYPE_6__*,TYPE_2__*) ; 
 int qsvenc_init_session (TYPE_6__*,TYPE_2__*) ; 

int ff_qsv_enc_init(AVCodecContext *avctx, QSVEncContext *q)
{
    int iopattern = 0;
    int opaque_alloc = 0;
    int ret;

    q->param.AsyncDepth = q->async_depth;

    q->async_fifo = av_fifo_alloc(q->async_depth * qsv_fifo_item_size());
    if (!q->async_fifo)
        return AVERROR(ENOMEM);

    if (avctx->hwaccel_context) {
        AVQSVContext *qsv = avctx->hwaccel_context;

        iopattern    = qsv->iopattern;
        opaque_alloc = qsv->opaque_alloc;
    }

    if (avctx->hw_frames_ctx) {
        AVHWFramesContext    *frames_ctx = (AVHWFramesContext*)avctx->hw_frames_ctx->data;
        AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;

        if (!iopattern) {
            if (frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)
                iopattern = MFX_IOPATTERN_IN_OPAQUE_MEMORY;
            else if (frames_hwctx->frame_type &
                     (MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET | MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET))
                iopattern = MFX_IOPATTERN_IN_VIDEO_MEMORY;
        }
    }

    if (!iopattern)
        iopattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY;
    q->param.IOPattern = iopattern;

    ret = qsvenc_init_session(avctx, q);
    if (ret < 0)
        return ret;

    ret = MFXQueryVersion(q->session,&q->ver);
    if (ret < 0) {
        return ff_qsv_print_error(avctx, ret,
                                  "Error querying mfx version");
    }

    // in the mfxInfoMFX struct, JPEG is different from other codecs
    switch (avctx->codec_id) {
    case AV_CODEC_ID_MJPEG:
        ret = init_video_param_jpeg(avctx, q);
        break;
    default:
        ret = init_video_param(avctx, q);
        break;
    }
    if (ret < 0)
        return ret;

    if (avctx->hwaccel_context) {
        AVQSVContext *qsv = avctx->hwaccel_context;
        int i, j;

        q->extparam = av_mallocz_array(qsv->nb_ext_buffers + q->nb_extparam_internal,
                                       sizeof(*q->extparam));
        if (!q->extparam)
            return AVERROR(ENOMEM);

        q->param.ExtParam = q->extparam;
        for (i = 0; i < qsv->nb_ext_buffers; i++)
            q->param.ExtParam[i] = qsv->ext_buffers[i];
        q->param.NumExtParam = qsv->nb_ext_buffers;

        for (i = 0; i < q->nb_extparam_internal; i++) {
            for (j = 0; j < qsv->nb_ext_buffers; j++) {
                if (qsv->ext_buffers[j]->BufferId == q->extparam_internal[i]->BufferId)
                    break;
            }
            if (j < qsv->nb_ext_buffers)
                continue;

            q->param.ExtParam[q->param.NumExtParam++] = q->extparam_internal[i];
        }
    } else {
        q->param.ExtParam    = q->extparam_internal;
        q->param.NumExtParam = q->nb_extparam_internal;
    }

    ret = MFXVideoENCODE_Query(q->session, &q->param, &q->param);
    if (ret == MFX_WRN_PARTIAL_ACCELERATION) {
        av_log(avctx, AV_LOG_WARNING, "Encoder will work with partial HW acceleration\n");
    } else if (ret < 0) {
        return ff_qsv_print_error(avctx, ret,
                                  "Error querying encoder params");
    }

    ret = MFXVideoENCODE_QueryIOSurf(q->session, &q->param, &q->req);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error querying (IOSurf) the encoding parameters");

    if (opaque_alloc) {
        ret = qsv_init_opaque_alloc(avctx, q);
        if (ret < 0)
            return ret;
    }

    ret = MFXVideoENCODE_Init(q->session, &q->param);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error initializing the encoder");
    else if (ret > 0)
        ff_qsv_print_warning(avctx, ret,
                             "Warning in encoder initialization");

    switch (avctx->codec_id) {
    case AV_CODEC_ID_MJPEG:
        ret = qsv_retrieve_enc_jpeg_params(avctx, q);
        break;
    case AV_CODEC_ID_VP9:
        ret = qsv_retrieve_enc_vp9_params(avctx, q);
        break;
    default:
        ret = qsv_retrieve_enc_params(avctx, q);
        break;
    }
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error retrieving encoding parameters.\n");
        return ret;
    }

    q->avctx = avctx;

    return 0;
}