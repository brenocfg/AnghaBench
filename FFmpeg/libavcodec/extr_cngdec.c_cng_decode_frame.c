#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_14__ {int frame_size; TYPE_1__* internal; TYPE_2__* priv_data; } ;
struct TYPE_13__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_12__ {int size; int* data; } ;
struct TYPE_11__ {int target_energy; int* target_refl_coef; int order; int inited; int energy; double* refl_coef; float* excitation; double* filter_out; int /*<<< orphan*/  lpc_coef; int /*<<< orphan*/  lfg; } ;
struct TYPE_10__ {int skip_samples; } ;
typedef  TYPE_2__ CNGContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_clip_int16 (double) ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_celp_lp_synthesis_filterf (double*,int /*<<< orphan*/ ,float*,int,int) ; 
 int ff_exp10 (int) ; 
 int ff_get_buffer (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_lpc_coefs (int /*<<< orphan*/ ,double*,int) ; 
 int /*<<< orphan*/  memcpy (double*,double*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 float sqrt (float) ; 

__attribute__((used)) static int cng_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame = data;
    CNGContext *p = avctx->priv_data;
    int buf_size  = avpkt->size;
    int ret, i;
    int16_t *buf_out;
    float e = 1.0;
    float scaling;

    if (avpkt->size) {
        int dbov = -avpkt->data[0];
        p->target_energy = 1081109975 * ff_exp10(dbov / 10.0) * 0.75;
        memset(p->target_refl_coef, 0, p->order * sizeof(*p->target_refl_coef));
        for (i = 0; i < FFMIN(avpkt->size - 1, p->order); i++) {
            p->target_refl_coef[i] = (avpkt->data[1 + i] - 127) / 128.0;
        }
    }

    if (avctx->internal->skip_samples > 10 * avctx->frame_size) {
        avctx->internal->skip_samples = 0;
        return AVERROR_INVALIDDATA;
    }

    if (p->inited) {
        p->energy = p->energy / 2 + p->target_energy / 2;
        for (i = 0; i < p->order; i++)
            p->refl_coef[i] = 0.6 *p->refl_coef[i] + 0.4 * p->target_refl_coef[i];
    } else {
        p->energy = p->target_energy;
        memcpy(p->refl_coef, p->target_refl_coef, p->order * sizeof(*p->refl_coef));
        p->inited = 1;
    }
    make_lpc_coefs(p->lpc_coef, p->refl_coef, p->order);

    for (i = 0; i < p->order; i++)
        e *= 1.0 - p->refl_coef[i]*p->refl_coef[i];

    scaling = sqrt(e * p->energy / 1081109975);
    for (i = 0; i < avctx->frame_size; i++) {
        int r = (av_lfg_get(&p->lfg) & 0xffff) - 0x8000;
        p->excitation[i] = scaling * r;
    }
    ff_celp_lp_synthesis_filterf(p->filter_out + p->order, p->lpc_coef,
                                 p->excitation, avctx->frame_size, p->order);

    frame->nb_samples = avctx->frame_size;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    buf_out = (int16_t *)frame->data[0];
    for (i = 0; i < avctx->frame_size; i++)
        buf_out[i] = av_clip_int16(p->filter_out[i + p->order]);
    memcpy(p->filter_out, p->filter_out + avctx->frame_size,
           p->order * sizeof(*p->filter_out));

    *got_frame_ptr = 1;

    return buf_size;
}