#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int width; int height; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static int v410_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                             const AVFrame *pic, int *got_packet)
{
    uint8_t *dst;
    uint16_t *y, *u, *v;
    uint32_t val;
    int i, j, ret;

    if ((ret = ff_alloc_packet2(avctx, pkt, avctx->width * avctx->height * 4,
                                            avctx->width * avctx->height * 4)) < 0)
        return ret;
    dst = pkt->data;

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    avctx->coded_frame->key_frame = 1;
    avctx->coded_frame->pict_type = AV_PICTURE_TYPE_I;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    y = (uint16_t *)pic->data[0];
    u = (uint16_t *)pic->data[1];
    v = (uint16_t *)pic->data[2];

    for (i = 0; i < avctx->height; i++) {
        for (j = 0; j < avctx->width; j++) {
            val  = u[j] << 2;
            val |= y[j] << 12;
            val |= (uint32_t) v[j] << 22;
            AV_WL32(dst, val);
            dst += 4;
        }
        y += pic->linesize[0] >> 1;
        u += pic->linesize[1] >> 1;
        v += pic->linesize[2] >> 1;
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}