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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_13__ {scalar_t__ codec_id; int channels; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int nb_samples; scalar_t__ extended_data; } ;
struct TYPE_11__ {int* data; int size; } ;
struct TYPE_10__ {int /*<<< orphan*/ * chd; } ;
typedef  TYPE_1__ MACEContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_MACE3 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  chomp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  chomp6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mace_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    int16_t **samples;
    MACEContext *ctx = avctx->priv_data;
    int i, j, k, l, ret;
    int is_mace3 = (avctx->codec_id == AV_CODEC_ID_MACE3);

    if (buf_size % (avctx->channels << is_mace3)) {
        av_log(avctx, AV_LOG_ERROR, "buffer size %d is odd\n", buf_size);
        buf_size -= buf_size % (avctx->channels << is_mace3);
        if (!buf_size)
            return AVERROR_INVALIDDATA;
    }

    /* get output buffer */
    frame->nb_samples = 3 * (buf_size << (1 - is_mace3)) / avctx->channels;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples = (int16_t **)frame->extended_data;

    for(i = 0; i < avctx->channels; i++) {
        int16_t *output = samples[i];

        for (j=0; j < buf_size / (avctx->channels << is_mace3); j++)
            for (k=0; k < (1 << is_mace3); k++) {
                uint8_t pkt = buf[(i << is_mace3) +
                                  (j*avctx->channels << is_mace3) + k];

                uint8_t val[2][3] = {{pkt >> 5, (pkt >> 3) & 3, pkt & 7 },
                                     {pkt & 7 , (pkt >> 3) & 3, pkt >> 5}};

                for (l=0; l < 3; l++) {
                    if (is_mace3)
                        chomp3(&ctx->chd[i], output, val[1][l], l);
                    else
                        chomp6(&ctx->chd[i], output, val[0][l], l);

                    output += 1 << (1-is_mace3);
                }
            }
    }

    *got_frame_ptr = 1;

    return buf_size;
}