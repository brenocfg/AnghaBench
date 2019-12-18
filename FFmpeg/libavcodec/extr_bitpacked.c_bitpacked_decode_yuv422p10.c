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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int width; int height; } ;
struct TYPE_10__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bitpacked_decode_yuv422p10(AVCodecContext *avctx, AVFrame *frame,
                                      AVPacket *avpkt)
{
    uint64_t frame_size = (uint64_t)avctx->width * (uint64_t)avctx->height * 20;
    uint64_t packet_size = (uint64_t)avpkt->size * 8;
    GetBitContext bc;
    uint16_t *y, *u, *v;
    int ret, i, j;

    ret = ff_get_buffer(avctx, frame, 0);
    if (ret < 0)
        return ret;

    if (frame_size > packet_size)
        return AVERROR_INVALIDDATA;

    if (avctx->width % 2)
        return AVERROR_PATCHWELCOME;

    ret = init_get_bits(&bc, avpkt->data, avctx->width * avctx->height * 20);
    if (ret)
        return ret;

    for (i = 0; i < avctx->height; i++) {
        y = (uint16_t*)(frame->data[0] + i * frame->linesize[0]);
        u = (uint16_t*)(frame->data[1] + i * frame->linesize[1]);
        v = (uint16_t*)(frame->data[2] + i * frame->linesize[2]);

        for (j = 0; j < avctx->width; j += 2) {
            *u++ = get_bits(&bc, 10);
            *y++ = get_bits(&bc, 10);
            *v++ = get_bits(&bc, 10);
            *y++ = get_bits(&bc, 10);
        }
    }

    return 0;
}