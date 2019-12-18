#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_8__ {int bits_per_raw_sample; int pix_fmt; int flags; scalar_t__ color_range; TYPE_1__* codec; scalar_t__ priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  studio_profile; } ;
struct TYPE_6__ {scalar_t__ id; int /*<<< orphan*/  pix_fmts; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVCOL_RANGE_MPEG ; 
 scalar_t__ AVCOL_RANGE_UNSPECIFIED ; 
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ AV_CODEC_ID_MSS2 ; 
 int AV_PIX_FMT_GRAY8 ; 
 int AV_PIX_FMT_YUV420P ; 
 scalar_t__ CONFIG_GRAY ; 
 int /*<<< orphan*/  av_assert1 (int /*<<< orphan*/ ) ; 
 int ff_get_format (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum AVPixelFormat h263_get_format(AVCodecContext *avctx)
{
    /* MPEG-4 Studio Profile only, not supported by hardware */
    if (avctx->bits_per_raw_sample > 8) {
        av_assert1(((MpegEncContext *)avctx->priv_data)->studio_profile);
        return avctx->pix_fmt;
    }

    if (avctx->codec->id == AV_CODEC_ID_MSS2)
        return AV_PIX_FMT_YUV420P;

    if (CONFIG_GRAY && (avctx->flags & AV_CODEC_FLAG_GRAY)) {
        if (avctx->color_range == AVCOL_RANGE_UNSPECIFIED)
            avctx->color_range = AVCOL_RANGE_MPEG;
        return AV_PIX_FMT_GRAY8;
    }

    return avctx->pix_fmt = ff_get_format(avctx, avctx->codec->pix_fmts);
}