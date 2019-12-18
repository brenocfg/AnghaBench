#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_12__ {int sample_rate; int /*<<< orphan*/ * priv_data; } ;
struct TYPE_11__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_10__ {int* data; int size; } ;
typedef  int /*<<< orphan*/  NellyMoserDecodeContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int NELLY_BLOCK_LEN ; 
 int NELLY_SAMPLES ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_packet_get_side_data (TYPE_1__*,float,int /*<<< orphan*/ *) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nelly_decode_block (int /*<<< orphan*/ *,int const*,float*) ; 

__attribute__((used)) static int decode_tag(AVCodecContext *avctx, void *data,
                      int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    const uint8_t *side=av_packet_get_side_data(avpkt, 'F', NULL);
    int buf_size = avpkt->size;
    NellyMoserDecodeContext *s = avctx->priv_data;
    int blocks, i, ret;
    float   *samples_flt;

    blocks     = buf_size / NELLY_BLOCK_LEN;

    if (blocks <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Packet is too small\n");
        return AVERROR_INVALIDDATA;
    }

    if (buf_size % NELLY_BLOCK_LEN) {
        av_log(avctx, AV_LOG_WARNING, "Leftover bytes: %d.\n",
               buf_size % NELLY_BLOCK_LEN);
    }
    /* Normal numbers of blocks for sample rates:
     *  8000 Hz - 1
     * 11025 Hz - 2
     * 16000 Hz - 3
     * 22050 Hz - 4
     * 44100 Hz - 8
     */
    if(side && blocks>1 && avctx->sample_rate%11025==0 && (1<<((side[0]>>2)&3)) == blocks)
        avctx->sample_rate= 11025*(blocks/2);

    /* get output buffer */
    frame->nb_samples = NELLY_SAMPLES * blocks;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples_flt = (float *)frame->data[0];

    for (i=0 ; i<blocks ; i++) {
        nelly_decode_block(s, buf, samples_flt);
        samples_flt += NELLY_SAMPLES;
        buf += NELLY_BLOCK_LEN;
    }

    *got_frame_ptr = 1;

    return buf_size;
}