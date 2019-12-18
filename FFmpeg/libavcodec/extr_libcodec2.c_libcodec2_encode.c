#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {int /*<<< orphan*/  block_align; TYPE_1__* priv_data; } ;
struct TYPE_12__ {scalar_t__* data; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  codec; } ;
typedef  TYPE_1__ LibCodec2Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  codec2_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libcodec2_encode(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *frame, int *got_packet_ptr)
{
    LibCodec2Context *c2 = avctx->priv_data;
    int16_t *samples = (int16_t *)frame->data[0];

    int ret = ff_alloc_packet2(avctx, avpkt, avctx->block_align, 0);
    if (ret < 0) {
        return ret;
    }

    codec2_encode(c2->codec, avpkt->data, samples);
    *got_packet_ptr = 1;

    return 0;
}