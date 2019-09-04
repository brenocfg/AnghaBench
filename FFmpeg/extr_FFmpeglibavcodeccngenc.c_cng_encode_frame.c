#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  double int16_t ;
struct TYPE_14__ {TYPE_1__* priv_data; } ;
struct TYPE_13__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_12__ {int* data; int size; } ;
struct TYPE_11__ {int order; double* samples32; int* ref_coef; int /*<<< orphan*/  lpc; } ;
typedef  TYPE_1__ CNGContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int av_clip_uintp2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_alloc_packet2 (TYPE_4__*,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ff_lpc_calc_ref_coefs (int /*<<< orphan*/ *,double*,int,int*) ; 
 int /*<<< orphan*/  floor (double) ; 
 int log10 (double) ; 

__attribute__((used)) static int cng_encode_frame(AVCodecContext *avctx, AVPacket *avpkt,
                            const AVFrame *frame, int *got_packet_ptr)
{
    CNGContext *p = avctx->priv_data;
    int ret, i;
    double energy = 0;
    int qdbov;
    int16_t *samples = (int16_t*) frame->data[0];

    if ((ret = ff_alloc_packet2(avctx, avpkt, 1 + p->order, 1 + p->order))) {
        av_log(avctx, AV_LOG_ERROR, "Error getting output packet\n");
        return ret;
    }

    for (i = 0; i < frame->nb_samples; i++) {
        p->samples32[i] = samples[i];
        energy += samples[i] * samples[i];
    }
    energy /= frame->nb_samples;
    if (energy > 0) {
        double dbov = 10 * log10(energy / 1081109975);
        qdbov = av_clip_uintp2(-floor(dbov), 7);
    } else {
        qdbov = 127;
    }
    ff_lpc_calc_ref_coefs(&p->lpc, p->samples32, p->order, p->ref_coef);
    avpkt->data[0] = qdbov;
    for (i = 0; i < p->order; i++)
        avpkt->data[1 + i] = p->ref_coef[i] * 127 + 127;

    *got_packet_ptr = 1;
    av_assert1(avpkt->size == 1 + p->order);

    return 0;
}