#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_16__ {int size; int bits_per_subpacket; int bits_per_subpdiv; int ch_idx; scalar_t__ num_channels; int /*<<< orphan*/  joint_stereo; } ;
struct TYPE_15__ {int block_align; TYPE_1__* priv_data; } ;
struct TYPE_14__ {scalar_t__ extended_data; int /*<<< orphan*/  nb_samples; } ;
struct TYPE_13__ {int* data; int size; } ;
struct TYPE_12__ {int discarded_packets; int num_subpackets; int /*<<< orphan*/  gb; TYPE_8__* subpacket; int /*<<< orphan*/  samples_per_channel; } ;
typedef  TYPE_1__ COOKContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int decode_subpacket (TYPE_1__*,TYPE_8__*,int const*,float**) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cook_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    COOKContext *q = avctx->priv_data;
    float **samples = NULL;
    int i, ret;
    int offset = 0;
    int chidx = 0;

    if (buf_size < avctx->block_align)
        return buf_size;

    /* get output buffer */
    if (q->discarded_packets >= 2) {
        frame->nb_samples = q->samples_per_channel;
        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
            return ret;
        samples = (float **)frame->extended_data;
    }

    /* estimate subpacket sizes */
    q->subpacket[0].size = avctx->block_align;

    for (i = 1; i < q->num_subpackets; i++) {
        q->subpacket[i].size = 2 * buf[avctx->block_align - q->num_subpackets + i];
        q->subpacket[0].size -= q->subpacket[i].size + 1;
        if (q->subpacket[0].size < 0) {
            av_log(avctx, AV_LOG_DEBUG,
                   "frame subpacket size total > avctx->block_align!\n");
            return AVERROR_INVALIDDATA;
        }
    }

    /* decode supbackets */
    for (i = 0; i < q->num_subpackets; i++) {
        q->subpacket[i].bits_per_subpacket = (q->subpacket[i].size * 8) >>
                                              q->subpacket[i].bits_per_subpdiv;
        q->subpacket[i].ch_idx = chidx;
        av_log(avctx, AV_LOG_DEBUG,
               "subpacket[%i] size %i js %i %i block_align %i\n",
               i, q->subpacket[i].size, q->subpacket[i].joint_stereo, offset,
               avctx->block_align);

        if ((ret = decode_subpacket(q, &q->subpacket[i], buf + offset, samples)) < 0)
            return ret;
        offset += q->subpacket[i].size;
        chidx += q->subpacket[i].num_channels;
        av_log(avctx, AV_LOG_DEBUG, "subpacket[%i] %i %i\n",
               i, q->subpacket[i].size * 8, get_bits_count(&q->gb));
    }

    /* Discard the first two frames: no valid audio. */
    if (q->discarded_packets < 2) {
        q->discarded_packets++;
        *got_frame_ptr = 0;
        return avctx->block_align;
    }

    *got_frame_ptr = 1;

    return avctx->block_align;
}