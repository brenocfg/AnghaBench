#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {TYPE_1__* ch; } ;
struct TYPE_22__ {float* scoefs; float lambda; size_t cur_channel; float random_state; int /*<<< orphan*/  (* abs_pow34 ) (float*,float*,int) ;TYPE_3__* fdsp; TYPE_2__ psy; } ;
struct TYPE_21__ {float sample_rate; double bit_rate; int flags; float channels; int cutoff; } ;
struct TYPE_20__ {float energy; float spread; float threshold; } ;
struct TYPE_18__ {int num_windows; int* group_len; int num_swb; int* swb_offset; int* swb_sizes; } ;
struct TYPE_19__ {scalar_t__* band_type; int* sf_idx; float* pns_ener; float* coeffs; scalar_t__* zeroes; scalar_t__* band_alt; TYPE_4__ ics; } ;
struct TYPE_17__ {float (* scalarproduct_float ) (float*,float*,int) ;int /*<<< orphan*/  (* vector_fmul_scalar ) (float*,float*,float,int) ;} ;
struct TYPE_15__ {TYPE_6__* psy_bands; } ;
typedef  TYPE_5__ SingleChannelElement ;
typedef  TYPE_6__ FFPsyBand ;
typedef  TYPE_7__ AVCodecContext ;
typedef  TYPE_8__ AACEncContext ;

/* Variables and functions */
 float AAC_CUTOFF_FROM_BITRATE (int,int,int) ; 
 int AV_CODEC_FLAG_QSCALE ; 
 float FFMAX (float,float const) ; 
 float FFMIN (float,float const) ; 
 int /*<<< orphan*/  INFINITY ; 
 scalar_t__ NOISE_BT ; 
 float NOISE_LAMBDA_REPLACE ; 
 float NOISE_LOW_LIMIT ; 
 float NOISE_SPREAD_THRESHOLD ; 
 int POW_SF2_ZERO ; 
 int SCALE_DIFF_ZERO ; 
 int SCALE_MAX_DIFF ; 
 int av_clip (int /*<<< orphan*/ ,int,int) ; 
 float const av_clipf (float,float,float) ; 
 float* ff_aac_pow2sf_tab ; 
 int /*<<< orphan*/  ff_init_nextband_map (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_sfdelta_can_remove_band (TYPE_5__*,int /*<<< orphan*/ *,int,int) ; 
 float lcg_random (float) ; 
 int log2f (float) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ quantize_band_cost (TYPE_8__*,float*,float*,int,int,scalar_t__,float const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundf (int) ; 
 float sqrtf (float) ; 
 float stub1 (float*,float*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,float,int) ; 
 float stub3 (float*,float*,int) ; 
 int /*<<< orphan*/  stub4 (float*,float*,int) ; 
 int /*<<< orphan*/  stub5 (float*,float*,int) ; 

__attribute__((used)) static void search_for_pns(AACEncContext *s, AVCodecContext *avctx, SingleChannelElement *sce)
{
    FFPsyBand *band;
    int w, g, w2, i;
    int wlen = 1024 / sce->ics.num_windows;
    int bandwidth, cutoff;
    float *PNS = &s->scoefs[0*128], *PNS34 = &s->scoefs[1*128];
    float *NOR34 = &s->scoefs[3*128];
    uint8_t nextband[128];
    const float lambda = s->lambda;
    const float freq_mult = avctx->sample_rate*0.5f/wlen;
    const float thr_mult = NOISE_LAMBDA_REPLACE*(100.0f/lambda);
    const float spread_threshold = FFMIN(0.75f, NOISE_SPREAD_THRESHOLD*FFMAX(0.5f, lambda/100.f));
    const float dist_bias = av_clipf(4.f * 120 / lambda, 0.25f, 4.0f);
    const float pns_transient_energy_r = FFMIN(0.7f, lambda / 140.f);

    int refbits = avctx->bit_rate * 1024.0 / avctx->sample_rate
        / ((avctx->flags & AV_CODEC_FLAG_QSCALE) ? 2.0f : avctx->channels)
        * (lambda / 120.f);

    /** Keep this in sync with twoloop's cutoff selection */
    float rate_bandwidth_multiplier = 1.5f;
    int prev = -1000, prev_sf = -1;
    int frame_bit_rate = (avctx->flags & AV_CODEC_FLAG_QSCALE)
        ? (refbits * rate_bandwidth_multiplier * avctx->sample_rate / 1024)
        : (avctx->bit_rate / avctx->channels);

    frame_bit_rate *= 1.15f;

    if (avctx->cutoff > 0) {
        bandwidth = avctx->cutoff;
    } else {
        bandwidth = FFMAX(3000, AAC_CUTOFF_FROM_BITRATE(frame_bit_rate, 1, avctx->sample_rate));
    }

    cutoff = bandwidth * 2 * wlen / avctx->sample_rate;

    memcpy(sce->band_alt, sce->band_type, sizeof(sce->band_type));
    ff_init_nextband_map(sce, nextband);
    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
        int wstart = w*128;
        for (g = 0; g < sce->ics.num_swb; g++) {
            int noise_sfi;
            float dist1 = 0.0f, dist2 = 0.0f, noise_amp;
            float pns_energy = 0.0f, pns_tgt_energy, energy_ratio, dist_thresh;
            float sfb_energy = 0.0f, threshold = 0.0f, spread = 2.0f;
            float min_energy = -1.0f, max_energy = 0.0f;
            const int start = wstart+sce->ics.swb_offset[g];
            const float freq = (start-wstart)*freq_mult;
            const float freq_boost = FFMAX(0.88f*freq/NOISE_LOW_LIMIT, 1.0f);
            if (freq < NOISE_LOW_LIMIT || (start-wstart) >= cutoff) {
                if (!sce->zeroes[w*16+g])
                    prev_sf = sce->sf_idx[w*16+g];
                continue;
            }
            for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {
                band = &s->psy.ch[s->cur_channel].psy_bands[(w+w2)*16+g];
                sfb_energy += band->energy;
                spread     = FFMIN(spread, band->spread);
                threshold  += band->threshold;
                if (!w2) {
                    min_energy = max_energy = band->energy;
                } else {
                    min_energy = FFMIN(min_energy, band->energy);
                    max_energy = FFMAX(max_energy, band->energy);
                }
            }

            /* Ramps down at ~8000Hz and loosens the dist threshold */
            dist_thresh = av_clipf(2.5f*NOISE_LOW_LIMIT/freq, 0.5f, 2.5f) * dist_bias;

            /* PNS is acceptable when all of these are true:
             * 1. high spread energy (noise-like band)
             * 2. near-threshold energy (high PE means the random nature of PNS content will be noticed)
             * 3. on short window groups, all windows have similar energy (variations in energy would be destroyed by PNS)
             *
             * At this stage, point 2 is relaxed for zeroed bands near the noise threshold (hole avoidance is more important)
             */
            if ((!sce->zeroes[w*16+g] && !ff_sfdelta_can_remove_band(sce, nextband, prev_sf, w*16+g)) ||
                ((sce->zeroes[w*16+g] || !sce->band_alt[w*16+g]) && sfb_energy < threshold*sqrtf(1.0f/freq_boost)) || spread < spread_threshold ||
                (!sce->zeroes[w*16+g] && sce->band_alt[w*16+g] && sfb_energy > threshold*thr_mult*freq_boost) ||
                min_energy < pns_transient_energy_r * max_energy ) {
                sce->pns_ener[w*16+g] = sfb_energy;
                if (!sce->zeroes[w*16+g])
                    prev_sf = sce->sf_idx[w*16+g];
                continue;
            }

            pns_tgt_energy = sfb_energy*FFMIN(1.0f, spread*spread);
            noise_sfi = av_clip(roundf(log2f(pns_tgt_energy)*2), -100, 155); /* Quantize */
            noise_amp = -ff_aac_pow2sf_tab[noise_sfi + POW_SF2_ZERO];    /* Dequantize */
            if (prev != -1000) {
                int noise_sfdiff = noise_sfi - prev + SCALE_DIFF_ZERO;
                if (noise_sfdiff < 0 || noise_sfdiff > 2*SCALE_MAX_DIFF) {
                    if (!sce->zeroes[w*16+g])
                        prev_sf = sce->sf_idx[w*16+g];
                    continue;
                }
            }
            for (w2 = 0; w2 < sce->ics.group_len[w]; w2++) {
                float band_energy, scale, pns_senergy;
                const int start_c = (w+w2)*128+sce->ics.swb_offset[g];
                band = &s->psy.ch[s->cur_channel].psy_bands[(w+w2)*16+g];
                for (i = 0; i < sce->ics.swb_sizes[g]; i++) {
                    s->random_state  = lcg_random(s->random_state);
                    PNS[i] = s->random_state;
                }
                band_energy = s->fdsp->scalarproduct_float(PNS, PNS, sce->ics.swb_sizes[g]);
                scale = noise_amp/sqrtf(band_energy);
                s->fdsp->vector_fmul_scalar(PNS, PNS, scale, sce->ics.swb_sizes[g]);
                pns_senergy = s->fdsp->scalarproduct_float(PNS, PNS, sce->ics.swb_sizes[g]);
                pns_energy += pns_senergy;
                s->abs_pow34(NOR34, &sce->coeffs[start_c], sce->ics.swb_sizes[g]);
                s->abs_pow34(PNS34, PNS, sce->ics.swb_sizes[g]);
                dist1 += quantize_band_cost(s, &sce->coeffs[start_c],
                                            NOR34,
                                            sce->ics.swb_sizes[g],
                                            sce->sf_idx[(w+w2)*16+g],
                                            sce->band_alt[(w+w2)*16+g],
                                            lambda/band->threshold, INFINITY, NULL, NULL, 0);
                /* Estimate rd on average as 5 bits for SF, 4 for the CB, plus spread energy * lambda/thr */
                dist2 += band->energy/(band->spread*band->spread)*lambda*dist_thresh/band->threshold;
            }
            if (g && sce->band_type[w*16+g-1] == NOISE_BT) {
                dist2 += 5;
            } else {
                dist2 += 9;
            }
            energy_ratio = pns_tgt_energy/pns_energy; /* Compensates for quantization error */
            sce->pns_ener[w*16+g] = energy_ratio*pns_tgt_energy;
            if (sce->zeroes[w*16+g] || !sce->band_alt[w*16+g] || (energy_ratio > 0.85f && energy_ratio < 1.25f && dist2 < dist1)) {
                sce->band_type[w*16+g] = NOISE_BT;
                sce->zeroes[w*16+g] = 0;
                prev = noise_sfi;
            } else {
                if (!sce->zeroes[w*16+g])
                    prev_sf = sce->sf_idx[w*16+g];
            }
        }
    }
}