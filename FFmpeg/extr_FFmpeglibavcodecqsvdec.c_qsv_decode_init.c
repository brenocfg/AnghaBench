#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_23__ {int BitDepthLuma; int BitDepthChroma; int Shift; int Width; int Height; int /*<<< orphan*/  PicStruct; int /*<<< orphan*/  ChromaFormat; int /*<<< orphan*/  FourCC; } ;
struct TYPE_24__ {int CodecId; scalar_t__ CodecLevel; TYPE_2__ FrameInfo; int /*<<< orphan*/  CodecProfile; } ;
struct TYPE_25__ {int IOPattern; int AsyncDepth; TYPE_3__ mfx; int /*<<< orphan*/  NumExtParam; int /*<<< orphan*/  ExtParam; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ mfxVideoParam ;
typedef  int /*<<< orphan*/ * mfxSession ;
struct TYPE_30__ {TYPE_6__* hwctx; } ;
struct TYPE_29__ {TYPE_1__* comp; } ;
struct TYPE_28__ {int iopattern; int /*<<< orphan*/  nb_ext_buffers; int /*<<< orphan*/  ext_buffers; int /*<<< orphan*/ * session; } ;
struct TYPE_27__ {int frame_type; } ;
struct TYPE_26__ {int async_depth; int iopattern; TYPE_2__ frame_info; int /*<<< orphan*/  session; int /*<<< orphan*/  nb_ext_buffers; int /*<<< orphan*/  ext_buffers; int /*<<< orphan*/  fourcc; scalar_t__ async_fifo; } ;
struct TYPE_22__ {int depth; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_20__ {int coded_width; int coded_height; scalar_t__ pix_fmt; scalar_t__ level; int field_order; int /*<<< orphan*/  profile; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  hw_device_ctx; TYPE_13__* hw_frames_ctx; TYPE_7__* hwaccel_context; int /*<<< orphan*/  sw_pix_fmt; } ;
typedef  TYPE_5__ QSVContext ;
typedef  TYPE_6__ AVQSVFramesContext ;
typedef  TYPE_7__ AVQSVContext ;
typedef  TYPE_8__ AVPixFmtDescriptor ;
typedef  TYPE_9__ AVHWFramesContext ;
typedef  TYPE_10__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
#define  AV_FIELD_BB 130 
#define  AV_FIELD_PROGRESSIVE 129 
#define  AV_FIELD_TT 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_QSV ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FF_LEVEL_UNKNOWN ; 
 int MFXVideoDECODE_Init (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV420 ; 
 int MFX_IOPATTERN_OUT_OPAQUE_MEMORY ; 
 int MFX_IOPATTERN_OUT_SYSTEM_MEMORY ; 
 int MFX_IOPATTERN_OUT_VIDEO_MEMORY ; 
 scalar_t__ MFX_LEVEL_UNKNOWN ; 
 int MFX_MEMTYPE_OPAQUE_FRAME ; 
 int MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_FIELD_BFF ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_FIELD_TFF ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_PROGRESSIVE ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_UNKNOWN ; 
 scalar_t__ av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int ff_qsv_codec_id_to_mfx (int /*<<< orphan*/ ) ; 
 int ff_qsv_print_error (TYPE_10__*,int,char*) ; 
 int /*<<< orphan*/  ff_qsv_profile_to_mfx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qsv_fifo_item_size () ; 
 int qsv_init_session (TYPE_10__*,TYPE_5__*,int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qsv_decode_init(AVCodecContext *avctx, QSVContext *q)
{
    const AVPixFmtDescriptor *desc;
    mfxSession session = NULL;
    int iopattern = 0;
    mfxVideoParam param = { 0 };
    int frame_width  = avctx->coded_width;
    int frame_height = avctx->coded_height;
    int ret;

    desc = av_pix_fmt_desc_get(avctx->sw_pix_fmt);
    if (!desc)
        return AVERROR_BUG;

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

    ret = qsv_init_session(avctx, q, session, avctx->hw_frames_ctx, avctx->hw_device_ctx);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "Error initializing an MFX session\n");
        return ret;
    }

    ret = ff_qsv_codec_id_to_mfx(avctx->codec_id);
    if (ret < 0)
        return ret;

    param.mfx.CodecId      = ret;
    param.mfx.CodecProfile = ff_qsv_profile_to_mfx(avctx->codec_id, avctx->profile);
    param.mfx.CodecLevel   = avctx->level == FF_LEVEL_UNKNOWN ? MFX_LEVEL_UNKNOWN : avctx->level;

    param.mfx.FrameInfo.BitDepthLuma   = desc->comp[0].depth;
    param.mfx.FrameInfo.BitDepthChroma = desc->comp[0].depth;
    param.mfx.FrameInfo.Shift          = desc->comp[0].depth > 8;
    param.mfx.FrameInfo.FourCC         = q->fourcc;
    param.mfx.FrameInfo.Width          = frame_width;
    param.mfx.FrameInfo.Height         = frame_height;
    param.mfx.FrameInfo.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;

    switch (avctx->field_order) {
    case AV_FIELD_PROGRESSIVE:
        param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
        break;
    case AV_FIELD_TT:
        param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_FIELD_TFF;
        break;
    case AV_FIELD_BB:
        param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_FIELD_BFF;
        break;
    default:
        param.mfx.FrameInfo.PicStruct = MFX_PICSTRUCT_UNKNOWN;
        break;
    }

    param.IOPattern   = q->iopattern;
    param.AsyncDepth  = q->async_depth;
    param.ExtParam    = q->ext_buffers;
    param.NumExtParam = q->nb_ext_buffers;

    ret = MFXVideoDECODE_Init(q->session, &param);
    if (ret < 0)
        return ff_qsv_print_error(avctx, ret,
                                  "Error initializing the MFX video decoder");

    q->frame_info = param.mfx.FrameInfo;

    return 0;
}