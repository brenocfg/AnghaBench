#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ FrameRateExtN; scalar_t__ FrameRateExtD; scalar_t__ PicStruct; scalar_t__ Width; scalar_t__ Height; scalar_t__ FourCC; } ;
struct TYPE_11__ {scalar_t__ CodecId; scalar_t__ CodecProfile; scalar_t__ RateControlMethod; scalar_t__ LowPower; TYPE_1__ FrameInfo; } ;
struct TYPE_14__ {TYPE_2__ mfx; } ;
typedef  TYPE_5__ mfxVideoParam ;
typedef  scalar_t__ mfxStatus ;
struct TYPE_12__ {scalar_t__ FrameRateExtN; scalar_t__ FrameRateExtD; scalar_t__ PicStruct; scalar_t__ Width; scalar_t__ Height; scalar_t__ FourCC; } ;
struct TYPE_13__ {scalar_t__ CodecId; scalar_t__ CodecProfile; scalar_t__ RateControlMethod; scalar_t__ LowPower; TYPE_3__ FrameInfo; } ;
struct TYPE_16__ {TYPE_4__ mfx; } ;
struct TYPE_15__ {TYPE_8__ param; int /*<<< orphan*/  session; } ;
typedef  TYPE_6__ QSVEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ MFXVideoENCODE_Query (int /*<<< orphan*/ ,TYPE_8__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_enc_param(AVCodecContext *avctx, QSVEncContext *q)
{
    mfxVideoParam param_out = { .mfx.CodecId = q->param.mfx.CodecId };
    mfxStatus ret;

#define UNMATCH(x) (param_out.mfx.x != q->param.mfx.x)

    ret = MFXVideoENCODE_Query(q->session, &q->param, &param_out);

    if (ret < 0) {
        if (UNMATCH(CodecId))
            av_log(avctx, AV_LOG_ERROR, "Current codec type is unsupported\n");
        if (UNMATCH(CodecProfile))
            av_log(avctx, AV_LOG_ERROR, "Current profile is unsupported\n");
        if (UNMATCH(RateControlMethod))
            av_log(avctx, AV_LOG_ERROR, "Selected ratecontrol mode is unsupported\n");
        if (UNMATCH(LowPower))
              av_log(avctx, AV_LOG_ERROR, "Low power mode is unsupported\n");
        if (UNMATCH(FrameInfo.FrameRateExtN) || UNMATCH(FrameInfo.FrameRateExtD))
              av_log(avctx, AV_LOG_ERROR, "Current frame rate is unsupported\n");
        if (UNMATCH(FrameInfo.PicStruct))
              av_log(avctx, AV_LOG_ERROR, "Current picture structure is unsupported\n");
        if (UNMATCH(FrameInfo.Width) || UNMATCH(FrameInfo.Height))
              av_log(avctx, AV_LOG_ERROR, "Current resolution is unsupported\n");
        if (UNMATCH(FrameInfo.FourCC))
              av_log(avctx, AV_LOG_ERROR, "Current pixel format is unsupported\n");
        return 0;
    }
    return 1;
}