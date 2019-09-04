#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float* pf_gains_new; int /*<<< orphan*/  pf_period_new; } ;
struct TYPE_4__ {float pf_gain; int pf_octave; int pf_period; int pf_tapset; scalar_t__ framebits; TYPE_2__* block; int /*<<< orphan*/  pfilter; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ CeltFrame ;
typedef  TYPE_2__ CeltBlock ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_POSTFILTER_MINPERIOD ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_celt_model_tapset ; 
 float** ff_celt_postfilter_taps ; 
 int /*<<< orphan*/  ff_opus_rc_enc_cdf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_opus_rc_enc_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_opus_rc_enc_uint (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ff_opus_rc_put_raw (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ opus_rc_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void celt_enc_quant_pfilter(OpusRangeCoder *rc, CeltFrame *f)
{
    float gain = f->pf_gain;
    int txval, octave = f->pf_octave, period = f->pf_period, tapset = f->pf_tapset;

    ff_opus_rc_enc_log(rc, f->pfilter, 1);
    if (!f->pfilter)
        return;

    /* Octave */
    txval = FFMIN(octave, 6);
    ff_opus_rc_enc_uint(rc, txval, 6);
    octave = txval;
    /* Period */
    txval = av_clip(period - (16 << octave) + 1, 0, (1 << (4 + octave)) - 1);
    ff_opus_rc_put_raw(rc, period, 4 + octave);
    period = txval + (16 << octave) - 1;
    /* Gain */
    txval = FFMIN(((int)(gain / 0.09375f)) - 1, 7);
    ff_opus_rc_put_raw(rc, txval, 3);
    gain   = 0.09375f * (txval + 1);
    /* Tapset */
    if ((opus_rc_tell(rc) + 2) <= f->framebits)
        ff_opus_rc_enc_cdf(rc, tapset, ff_celt_model_tapset);
    else
        tapset = 0;
    /* Finally create the coeffs */
    for (int i = 0; i < 2; i++) {
        CeltBlock *block = &f->block[i];

        block->pf_period_new = FFMAX(period, CELT_POSTFILTER_MINPERIOD);
        block->pf_gains_new[0] = gain * ff_celt_postfilter_taps[tapset][0];
        block->pf_gains_new[1] = gain * ff_celt_postfilter_taps[tapset][1];
        block->pf_gains_new[2] = gain * ff_celt_postfilter_taps[tapset][2];
    }
}