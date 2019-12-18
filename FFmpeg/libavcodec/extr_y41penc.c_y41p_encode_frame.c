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
struct TYPE_11__ {double width; double height; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,double,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int y41p_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                             const AVFrame *pic, int *got_packet)
{
    uint8_t *dst;
    uint8_t *y, *u, *v;
    int i, j, ret;

    if ((ret = ff_alloc_packet2(avctx, pkt, avctx->width * avctx->height * 1.5, 0)) < 0)
        return ret;

    dst = pkt->data;

    for (i = avctx->height - 1; i >= 0; i--) {
        y = &pic->data[0][i * pic->linesize[0]];
        u = &pic->data[1][i * pic->linesize[1]];
        v = &pic->data[2][i * pic->linesize[2]];
        for (j = 0; j < avctx->width; j += 8) {
            *(dst++) = *(u++);
            *(dst++) = *(y++);
            *(dst++) = *(v++);
            *(dst++) = *(y++);

            *(dst++) = *(u++);
            *(dst++) = *(y++);
            *(dst++) = *(v++);
            *(dst++) = *(y++);

            *(dst++) = *(y++);
            *(dst++) = *(y++);
            *(dst++) = *(y++);
            *(dst++) = *(y++);
        }
    }

    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}