#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_31__ {int BitDepthLuma; int BitDepthChroma; int Shift; scalar_t__ FrameRateExtN; scalar_t__ FrameRateExtD; void* Height; void* Width; int /*<<< orphan*/  ChromaFormat; int /*<<< orphan*/  AspectRatioH; int /*<<< orphan*/  AspectRatioW; int /*<<< orphan*/  CropH; int /*<<< orphan*/  CropW; scalar_t__ CropY; scalar_t__ CropX; int /*<<< orphan*/  FourCC; } ;
struct TYPE_33__ {int CodecId; scalar_t__ CodecLevel; int Interleaved; scalar_t__ RestartInterval; int /*<<< orphan*/  Quality; TYPE_7__ FrameInfo; int /*<<< orphan*/  CodecProfile; } ;
struct TYPE_32__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_30__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_28__ {void* Height; void* Width; } ;
struct TYPE_29__ {TYPE_4__ Info; } ;
struct TYPE_27__ {scalar_t__ data; } ;
struct TYPE_26__ {int depth; } ;
struct TYPE_25__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_24__ {scalar_t__ pix_fmt; int sw_pix_fmt; scalar_t__ level; int /*<<< orphan*/  global_quality; TYPE_8__ time_base; TYPE_6__ framerate; TYPE_3__* hw_frames_ctx; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  codec_id; } ;
struct TYPE_23__ {TYPE_12__* hwctx; } ;
struct TYPE_22__ {TYPE_2__* comp; } ;
struct TYPE_21__ {TYPE_5__* surfaces; } ;
struct TYPE_19__ {TYPE_9__ mfx; } ;
struct TYPE_20__ {TYPE_10__ param; int /*<<< orphan*/  profile; } ;
typedef  TYPE_11__ QSVEncContext ;
typedef  TYPE_12__ AVQSVFramesContext ;
typedef  TYPE_13__ AVPixFmtDescriptor ;
typedef  TYPE_14__ AVHWFramesContext ;
typedef  TYPE_15__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 scalar_t__ AV_PIX_FMT_QSV ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV420 ; 
 int /*<<< orphan*/  av_clip (int /*<<< orphan*/ ,int,int) ; 
 TYPE_13__* av_pix_fmt_desc_get (int) ; 
 int ff_qsv_codec_id_to_mfx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_qsv_map_pixfmt (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_video_param_jpeg(AVCodecContext *avctx, QSVEncContext *q)
{
    enum AVPixelFormat sw_format = avctx->pix_fmt == AV_PIX_FMT_QSV ?
                                   avctx->sw_pix_fmt : avctx->pix_fmt;
    const AVPixFmtDescriptor *desc;
    int ret;

    ret = ff_qsv_codec_id_to_mfx(avctx->codec_id);
    if (ret < 0)
        return AVERROR_BUG;
    q->param.mfx.CodecId = ret;

    if (avctx->level > 0)
        q->param.mfx.CodecLevel = avctx->level;
    q->param.mfx.CodecProfile       = q->profile;

    desc = av_pix_fmt_desc_get(sw_format);
    if (!desc)
        return AVERROR_BUG;

    ff_qsv_map_pixfmt(sw_format, &q->param.mfx.FrameInfo.FourCC);

    q->param.mfx.FrameInfo.CropX          = 0;
    q->param.mfx.FrameInfo.CropY          = 0;
    q->param.mfx.FrameInfo.CropW          = avctx->width;
    q->param.mfx.FrameInfo.CropH          = avctx->height;
    q->param.mfx.FrameInfo.AspectRatioW   = avctx->sample_aspect_ratio.num;
    q->param.mfx.FrameInfo.AspectRatioH   = avctx->sample_aspect_ratio.den;
    q->param.mfx.FrameInfo.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    q->param.mfx.FrameInfo.BitDepthLuma   = desc->comp[0].depth;
    q->param.mfx.FrameInfo.BitDepthChroma = desc->comp[0].depth;
    q->param.mfx.FrameInfo.Shift          = desc->comp[0].depth > 8;

    q->param.mfx.FrameInfo.Width  = FFALIGN(avctx->width, 16);
    q->param.mfx.FrameInfo.Height = FFALIGN(avctx->height, 16);

    if (avctx->hw_frames_ctx) {
        AVHWFramesContext *frames_ctx    = (AVHWFramesContext *)avctx->hw_frames_ctx->data;
        AVQSVFramesContext *frames_hwctx = frames_ctx->hwctx;
        q->param.mfx.FrameInfo.Width  = frames_hwctx->surfaces[0].Info.Width;
        q->param.mfx.FrameInfo.Height = frames_hwctx->surfaces[0].Info.Height;
    }

    if (avctx->framerate.den > 0 && avctx->framerate.num > 0) {
        q->param.mfx.FrameInfo.FrameRateExtN = avctx->framerate.num;
        q->param.mfx.FrameInfo.FrameRateExtD = avctx->framerate.den;
    } else {
        q->param.mfx.FrameInfo.FrameRateExtN  = avctx->time_base.den;
        q->param.mfx.FrameInfo.FrameRateExtD  = avctx->time_base.num;
    }

    q->param.mfx.Interleaved          = 1;
    q->param.mfx.Quality              = av_clip(avctx->global_quality, 1, 100);
    q->param.mfx.RestartInterval      = 0;

    return 0;
}