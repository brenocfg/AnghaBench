#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int int16_t ;
struct TYPE_17__ {TYPE_2__* priv_data; } ;
struct TYPE_16__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_15__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* apply_qmf ) (int*,int*) ;} ;
struct TYPE_14__ {int bits_per_codeword; int* prev_samples; int prev_samples_pos; TYPE_1__ dsp; TYPE_10__* band; } ;
struct TYPE_12__ {int const scale_factor; scalar_t__ s_predictor; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ G722Context ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ PREV_SAMPLES_BUF_SIZE ; 
 void* av_clip_int16 (int) ; 
 int av_clip_intp2 (scalar_t__,int) ; 
 int* ff_g722_high_inv_quant ; 
 int /*<<< orphan*/  ff_g722_update_high_predictor (TYPE_10__*,int,int) ; 
 int /*<<< orphan*/  ff_g722_update_low_predictor (TYPE_10__*,int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int** low_inv_quants ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 

__attribute__((used)) static int g722_decode_frame(AVCodecContext *avctx, void *data,
                             int *got_frame_ptr, AVPacket *avpkt)
{
    G722Context *c = avctx->priv_data;
    AVFrame *frame = data;
    int16_t *out_buf;
    int j, ret;
    const int skip = 8 - c->bits_per_codeword;
    const int16_t *quantizer_table = low_inv_quants[skip];
    GetBitContext gb;

    /* get output buffer */
    frame->nb_samples = avpkt->size * 2;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    out_buf = (int16_t *)frame->data[0];

    ret = init_get_bits8(&gb, avpkt->data, avpkt->size);
    if (ret < 0)
        return ret;

    for (j = 0; j < avpkt->size; j++) {
        int ilow, ihigh, rlow, rhigh, dhigh;
        int xout[2];

        ihigh = get_bits(&gb, 2);
        ilow = get_bits(&gb, 6 - skip);
        skip_bits(&gb, skip);

        rlow = av_clip_intp2((c->band[0].scale_factor * quantizer_table[ilow] >> 10)
                      + c->band[0].s_predictor, 14);

        ff_g722_update_low_predictor(&c->band[0], ilow >> (2 - skip));

        dhigh = c->band[1].scale_factor * ff_g722_high_inv_quant[ihigh] >> 10;
        rhigh = av_clip_intp2(dhigh + c->band[1].s_predictor, 14);

        ff_g722_update_high_predictor(&c->band[1], dhigh, ihigh);

        c->prev_samples[c->prev_samples_pos++] = rlow + rhigh;
        c->prev_samples[c->prev_samples_pos++] = rlow - rhigh;
        c->dsp.apply_qmf(c->prev_samples + c->prev_samples_pos - 24, xout);
        *out_buf++ = av_clip_int16(xout[0] >> 11);
        *out_buf++ = av_clip_int16(xout[1] >> 11);
        if (c->prev_samples_pos >= PREV_SAMPLES_BUF_SIZE) {
            memmove(c->prev_samples, c->prev_samples + c->prev_samples_pos - 22,
                    22 * sizeof(c->prev_samples[0]));
            c->prev_samples_pos = 22;
        }
    }

    *got_frame_ptr = 1;

    return avpkt->size;
}