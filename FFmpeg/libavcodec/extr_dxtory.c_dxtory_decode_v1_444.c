#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {long long width; long long height; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_8__ {int** data; int /*<<< orphan*/ * linesize; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxtory_decode_v1_444(AVCodecContext *avctx, AVFrame *pic,
                                const uint8_t *src, int src_size)
{
    int h, w;
    uint8_t *Y, *U, *V;
    int ret;

    if (src_size < avctx->width * avctx->height * 3LL) {
        av_log(avctx, AV_LOG_ERROR, "packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    avctx->pix_fmt = AV_PIX_FMT_YUV444P;
    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    Y = pic->data[0];
    U = pic->data[1];
    V = pic->data[2];
    for (h = 0; h < avctx->height; h++) {
        for (w = 0; w < avctx->width; w++) {
            Y[w] = *src++;
            U[w] = *src++ ^ 0x80;
            V[w] = *src++ ^ 0x80;
        }
        Y += pic->linesize[0];
        U += pic->linesize[1];
        V += pic->linesize[2];
    }

    return 0;
}