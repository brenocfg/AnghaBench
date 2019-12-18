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
struct gsm_state {int dummy; } ;
typedef  int /*<<< orphan*/  gsm_signal ;
struct TYPE_11__ {int codec_id; int /*<<< orphan*/  block_align; struct gsm_state* priv_data; } ;
struct TYPE_10__ {scalar_t__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
#define  AV_CODEC_ID_GSM 129 
#define  AV_CODEC_ID_GSM_MS 128 
 int /*<<< orphan*/  GSM_FRAME_SIZE ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsm_encode (struct gsm_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libgsm_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                               const AVFrame *frame, int *got_packet_ptr)
{
    int ret;
    gsm_signal *samples = (gsm_signal *)frame->data[0];
    struct gsm_state *state = avctx->priv_data;

    if ((ret = ff_alloc_packet2(avctx, avpkt, avctx->block_align, 0)) < 0)
        return ret;

    switch(avctx->codec_id) {
    case AV_CODEC_ID_GSM:
        gsm_encode(state, samples, avpkt->data);
        break;
    case AV_CODEC_ID_GSM_MS:
        gsm_encode(state, samples,                  avpkt->data);
        gsm_encode(state, samples + GSM_FRAME_SIZE, avpkt->data + 32);
    }

    *got_packet_ptr = 1;
    return 0;
}