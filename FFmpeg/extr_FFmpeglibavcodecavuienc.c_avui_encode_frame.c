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
struct TYPE_11__ {scalar_t__ field_order; int height; int width; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int avui_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                             const AVFrame *pic, int *got_packet)
{
    uint8_t *dst;
    int i, j, skip, ret, size, interlaced;

    interlaced = avctx->field_order > AV_FIELD_PROGRESSIVE;

    if (avctx->height == 486) {
        skip = 10;
    } else {
        skip = 16;
    }
    size = 2 * avctx->width * (avctx->height + skip) + 8 * interlaced;
    if ((ret = ff_alloc_packet2(avctx, pkt, size, size)) < 0)
        return ret;
    dst = pkt->data;
    if (!interlaced) {
        memset(dst, 0, avctx->width * skip);
        dst += avctx->width * skip;
    }

    for (i = 0; i <= interlaced; i++) {
        uint8_t *src;
        if (interlaced && avctx->height == 486) {
            src = pic->data[0] + (1 - i) * pic->linesize[0];
        } else {
            src = pic->data[0] + i * pic->linesize[0];
        }
        memset(dst, 0, avctx->width * skip + 4 * i);
        dst += avctx->width * skip + 4 * i;
        for (j = 0; j < avctx->height; j += interlaced + 1) {
            memcpy(dst, src, avctx->width * 2);
            src += (interlaced + 1) * pic->linesize[0];
            dst += avctx->width * 2;
        }
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}