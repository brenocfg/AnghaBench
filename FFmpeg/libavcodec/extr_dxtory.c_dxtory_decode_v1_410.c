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
typedef  scalar_t__ uint8_t ;
struct TYPE_9__ {int width; int height; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_8__ {int* linesize; scalar_t__** data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_COPY32U (scalar_t__*,scalar_t__ const*) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV410P ; 
 long long FFALIGN (int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxtory_decode_v1_410(AVCodecContext *avctx, AVFrame *pic,
                                const uint8_t *src, int src_size)
{
    int h, w;
    uint8_t *Y1, *Y2, *Y3, *Y4, *U, *V;
    int ret;

    if (src_size < FFALIGN(avctx->width, 4) * FFALIGN(avctx->height, 4) * 9LL / 8) {
        av_log(avctx, AV_LOG_ERROR, "packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    avctx->pix_fmt = AV_PIX_FMT_YUV410P;
    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    Y1 = pic->data[0];
    Y2 = pic->data[0] + pic->linesize[0];
    Y3 = pic->data[0] + pic->linesize[0] * 2;
    Y4 = pic->data[0] + pic->linesize[0] * 3;
    U  = pic->data[1];
    V  = pic->data[2];
    for (h = 0; h < avctx->height; h += 4) {
        for (w = 0; w < avctx->width; w += 4) {
            AV_COPY32U(Y1 + w, src);
            AV_COPY32U(Y2 + w, src + 4);
            AV_COPY32U(Y3 + w, src + 8);
            AV_COPY32U(Y4 + w, src + 12);
            U[w >> 2] = src[16] + 0x80;
            V[w >> 2] = src[17] + 0x80;
            src += 18;
        }
        Y1 += pic->linesize[0] << 2;
        Y2 += pic->linesize[0] << 2;
        Y3 += pic->linesize[0] << 2;
        Y4 += pic->linesize[0] << 2;
        U  += pic->linesize[1];
        V  += pic->linesize[2];
    }

    return 0;
}