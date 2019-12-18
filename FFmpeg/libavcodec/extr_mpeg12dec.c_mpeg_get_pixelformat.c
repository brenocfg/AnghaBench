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
struct TYPE_8__ {int flags; scalar_t__ codec_id; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int chroma_format; } ;
struct TYPE_7__ {TYPE_1__ mpeg_enc_ctx; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ Mpeg1Context ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG_GRAY ; 
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 int AV_PIX_FMT_GRAY8 ; 
 scalar_t__ CONFIG_GRAY ; 
 int ff_thread_get_format (TYPE_3__*,int const*) ; 
 int* mpeg12_pixfmt_list_422 ; 
 int* mpeg12_pixfmt_list_444 ; 
 int* mpeg1_hwaccel_pixfmt_list_420 ; 
 int* mpeg2_hwaccel_pixfmt_list_420 ; 

__attribute__((used)) static enum AVPixelFormat mpeg_get_pixelformat(AVCodecContext *avctx)
{
    Mpeg1Context *s1  = avctx->priv_data;
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    const enum AVPixelFormat *pix_fmts;

    if (CONFIG_GRAY && (avctx->flags & AV_CODEC_FLAG_GRAY))
        return AV_PIX_FMT_GRAY8;

    if (s->chroma_format < 2)
        pix_fmts = avctx->codec_id == AV_CODEC_ID_MPEG1VIDEO ?
                                mpeg1_hwaccel_pixfmt_list_420 :
                                mpeg2_hwaccel_pixfmt_list_420;
    else if (s->chroma_format == 2)
        pix_fmts = mpeg12_pixfmt_list_422;
    else
        pix_fmts = mpeg12_pixfmt_list_444;

    return ff_thread_get_format(avctx, pix_fmts);
}