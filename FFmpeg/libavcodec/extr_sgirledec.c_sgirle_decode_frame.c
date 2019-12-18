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
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_10__ {int key_frame; int /*<<< orphan*/  pict_type; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int decode_sgirle8 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sgirle_decode_frame(AVCodecContext *avctx, void *data,
                               int *got_frame, AVPacket *avpkt)
{
    AVFrame *frame = data;
    int ret;

    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;

    ret = decode_sgirle8(avctx, frame->data[0], avpkt->data, avpkt->size,
                         avctx->width, avctx->height, frame->linesize[0]);
    if (ret < 0)
        return ret;

    frame->pict_type = AV_PICTURE_TYPE_I;
    frame->key_frame = 1;

    *got_frame = 1;

    return avpkt->size;
}