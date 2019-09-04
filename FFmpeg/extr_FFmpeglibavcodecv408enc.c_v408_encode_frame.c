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
typedef  void* uint8_t ;
struct TYPE_11__ {int width; int height; scalar_t__ codec_id; } ;
struct TYPE_10__ {void*** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_9__ {void** data; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_AYUV ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v408_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                             const AVFrame *pic, int *got_packet)
{
    uint8_t *dst;
    uint8_t *y, *u, *v, *a;
    int i, j, ret;

    if ((ret = ff_alloc_packet2(avctx, pkt, avctx->width * avctx->height * 4, 0)) < 0)
        return ret;
    dst = pkt->data;

    y = pic->data[0];
    u = pic->data[1];
    v = pic->data[2];
    a = pic->data[3];

    for (i = 0; i < avctx->height; i++) {
        for (j = 0; j < avctx->width; j++) {
           if (avctx->codec_id==AV_CODEC_ID_AYUV) {
                *dst++ = v[j];
                *dst++ = u[j];
                *dst++ = y[j];
                *dst++ = a[j];
            } else {
                *dst++ = u[j];
                *dst++ = y[j];
                *dst++ = v[j];
                *dst++ = a[j];
            }
        }
        y += pic->linesize[0];
        u += pic->linesize[1];
        v += pic->linesize[2];
        a += pic->linesize[3];
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}