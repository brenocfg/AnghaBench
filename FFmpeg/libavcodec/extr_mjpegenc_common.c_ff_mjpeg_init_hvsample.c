#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pix_fmt; TYPE_1__* codec; } ;
struct TYPE_4__ {scalar_t__ id; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_LJPEG ; 
 scalar_t__ AV_PIX_FMT_BGR0 ; 
 scalar_t__ AV_PIX_FMT_BGR24 ; 
 scalar_t__ AV_PIX_FMT_BGRA ; 
 scalar_t__ AV_PIX_FMT_YUV444P ; 
 scalar_t__ AV_PIX_FMT_YUVJ444P ; 
 int /*<<< orphan*/  av_pix_fmt_get_chroma_sub_sample (scalar_t__,int*,int*) ; 

void ff_mjpeg_init_hvsample(AVCodecContext *avctx, int hsample[4], int vsample[4])
{
    int chroma_h_shift, chroma_v_shift;

    av_pix_fmt_get_chroma_sub_sample(avctx->pix_fmt, &chroma_h_shift,
                                     &chroma_v_shift);
    if (avctx->codec->id == AV_CODEC_ID_LJPEG &&
        (   avctx->pix_fmt == AV_PIX_FMT_BGR0
         || avctx->pix_fmt == AV_PIX_FMT_BGRA
         || avctx->pix_fmt == AV_PIX_FMT_BGR24)) {
        vsample[0] = hsample[0] =
        vsample[1] = hsample[1] =
        vsample[2] = hsample[2] =
        vsample[3] = hsample[3] = 1;
    } else if (avctx->pix_fmt == AV_PIX_FMT_YUV444P || avctx->pix_fmt == AV_PIX_FMT_YUVJ444P) {
        vsample[0] = vsample[1] = vsample[2] = 2;
        hsample[0] = hsample[1] = hsample[2] = 1;
    } else {
        vsample[0] = 2;
        vsample[1] = 2 >> chroma_v_shift;
        vsample[2] = 2 >> chroma_v_shift;
        hsample[0] = 2;
        hsample[1] = 2 >> chroma_h_shift;
        hsample[2] = 2 >> chroma_h_shift;
    }
}