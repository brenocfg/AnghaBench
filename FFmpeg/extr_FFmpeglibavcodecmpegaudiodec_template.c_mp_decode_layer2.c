#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bit_rate; int nb_channels; scalar_t__ mode; int mode_ext; int*** sb_samples; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; int /*<<< orphan*/  lsf; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_1__ MPADecodeContext ;

/* Variables and functions */
 scalar_t__ MPA_JSTEREO ; 
 int MPA_MAX_CHANNELS ; 
 int SBLIMIT ; 
 int** division_tabs ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned char** ff_mpa_alloc_tables ; 
 int ff_mpa_l2_select_table (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* ff_mpa_quant_bits ; 
 int* ff_mpa_quant_steps ; 
 int* ff_mpa_sblimit_table ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* l1_unscale (int,int,int) ; 
 void* l2_unscale_group (int,int,int) ; 

__attribute__((used)) static int mp_decode_layer2(MPADecodeContext *s)
{
    int sblimit; /* number of used subbands */
    const unsigned char *alloc_table;
    int table, bit_alloc_bits, i, j, ch, bound, v;
    unsigned char bit_alloc[MPA_MAX_CHANNELS][SBLIMIT];
    unsigned char scale_code[MPA_MAX_CHANNELS][SBLIMIT];
    unsigned char scale_factors[MPA_MAX_CHANNELS][SBLIMIT][3], *sf;
    int scale, qindex, bits, steps, k, l, m, b;

    /* select decoding table */
    table = ff_mpa_l2_select_table(s->bit_rate / 1000, s->nb_channels,
                                   s->sample_rate, s->lsf);
    sblimit     = ff_mpa_sblimit_table[table];
    alloc_table = ff_mpa_alloc_tables[table];

    if (s->mode == MPA_JSTEREO)
        bound = (s->mode_ext + 1) * 4;
    else
        bound = sblimit;

    ff_dlog(s->avctx, "bound=%d sblimit=%d\n", bound, sblimit);

    /* sanity check */
    if (bound > sblimit)
        bound = sblimit;

    /* parse bit allocation */
    j = 0;
    for (i = 0; i < bound; i++) {
        bit_alloc_bits = alloc_table[j];
        for (ch = 0; ch < s->nb_channels; ch++)
            bit_alloc[ch][i] = get_bits(&s->gb, bit_alloc_bits);
        j += 1 << bit_alloc_bits;
    }
    for (i = bound; i < sblimit; i++) {
        bit_alloc_bits = alloc_table[j];
        v = get_bits(&s->gb, bit_alloc_bits);
        bit_alloc[0][i] = v;
        bit_alloc[1][i] = v;
        j += 1 << bit_alloc_bits;
    }

    /* scale codes */
    for (i = 0; i < sblimit; i++) {
        for (ch = 0; ch < s->nb_channels; ch++) {
            if (bit_alloc[ch][i])
                scale_code[ch][i] = get_bits(&s->gb, 2);
        }
    }

    /* scale factors */
    for (i = 0; i < sblimit; i++) {
        for (ch = 0; ch < s->nb_channels; ch++) {
            if (bit_alloc[ch][i]) {
                sf = scale_factors[ch][i];
                switch (scale_code[ch][i]) {
                default:
                case 0:
                    sf[0] = get_bits(&s->gb, 6);
                    sf[1] = get_bits(&s->gb, 6);
                    sf[2] = get_bits(&s->gb, 6);
                    break;
                case 2:
                    sf[0] = get_bits(&s->gb, 6);
                    sf[1] = sf[0];
                    sf[2] = sf[0];
                    break;
                case 1:
                    sf[0] = get_bits(&s->gb, 6);
                    sf[2] = get_bits(&s->gb, 6);
                    sf[1] = sf[0];
                    break;
                case 3:
                    sf[0] = get_bits(&s->gb, 6);
                    sf[2] = get_bits(&s->gb, 6);
                    sf[1] = sf[2];
                    break;
                }
            }
        }
    }

    /* samples */
    for (k = 0; k < 3; k++) {
        for (l = 0; l < 12; l += 3) {
            j = 0;
            for (i = 0; i < bound; i++) {
                bit_alloc_bits = alloc_table[j];
                for (ch = 0; ch < s->nb_channels; ch++) {
                    b = bit_alloc[ch][i];
                    if (b) {
                        scale = scale_factors[ch][i][k];
                        qindex = alloc_table[j+b];
                        bits = ff_mpa_quant_bits[qindex];
                        if (bits < 0) {
                            int v2;
                            /* 3 values at the same time */
                            v = get_bits(&s->gb, -bits);
                            v2 = division_tabs[qindex][v];
                            steps  = ff_mpa_quant_steps[qindex];

                            s->sb_samples[ch][k * 12 + l + 0][i] =
                                l2_unscale_group(steps,  v2       & 15, scale);
                            s->sb_samples[ch][k * 12 + l + 1][i] =
                                l2_unscale_group(steps, (v2 >> 4) & 15, scale);
                            s->sb_samples[ch][k * 12 + l + 2][i] =
                                l2_unscale_group(steps,  v2 >> 8      , scale);
                        } else {
                            for (m = 0; m < 3; m++) {
                                v = get_bits(&s->gb, bits);
                                v = l1_unscale(bits - 1, v, scale);
                                s->sb_samples[ch][k * 12 + l + m][i] = v;
                            }
                        }
                    } else {
                        s->sb_samples[ch][k * 12 + l + 0][i] = 0;
                        s->sb_samples[ch][k * 12 + l + 1][i] = 0;
                        s->sb_samples[ch][k * 12 + l + 2][i] = 0;
                    }
                }
                /* next subband in alloc table */
                j += 1 << bit_alloc_bits;
            }
            /* XXX: find a way to avoid this duplication of code */
            for (i = bound; i < sblimit; i++) {
                bit_alloc_bits = alloc_table[j];
                b = bit_alloc[0][i];
                if (b) {
                    int mant, scale0, scale1;
                    scale0 = scale_factors[0][i][k];
                    scale1 = scale_factors[1][i][k];
                    qindex = alloc_table[j+b];
                    bits = ff_mpa_quant_bits[qindex];
                    if (bits < 0) {
                        /* 3 values at the same time */
                        v = get_bits(&s->gb, -bits);
                        steps = ff_mpa_quant_steps[qindex];
                        mant = v % steps;
                        v = v / steps;
                        s->sb_samples[0][k * 12 + l + 0][i] =
                            l2_unscale_group(steps, mant, scale0);
                        s->sb_samples[1][k * 12 + l + 0][i] =
                            l2_unscale_group(steps, mant, scale1);
                        mant = v % steps;
                        v = v / steps;
                        s->sb_samples[0][k * 12 + l + 1][i] =
                            l2_unscale_group(steps, mant, scale0);
                        s->sb_samples[1][k * 12 + l + 1][i] =
                            l2_unscale_group(steps, mant, scale1);
                        s->sb_samples[0][k * 12 + l + 2][i] =
                            l2_unscale_group(steps, v, scale0);
                        s->sb_samples[1][k * 12 + l + 2][i] =
                            l2_unscale_group(steps, v, scale1);
                    } else {
                        for (m = 0; m < 3; m++) {
                            mant = get_bits(&s->gb, bits);
                            s->sb_samples[0][k * 12 + l + m][i] =
                                l1_unscale(bits - 1, mant, scale0);
                            s->sb_samples[1][k * 12 + l + m][i] =
                                l1_unscale(bits - 1, mant, scale1);
                        }
                    }
                } else {
                    s->sb_samples[0][k * 12 + l + 0][i] = 0;
                    s->sb_samples[0][k * 12 + l + 1][i] = 0;
                    s->sb_samples[0][k * 12 + l + 2][i] = 0;
                    s->sb_samples[1][k * 12 + l + 0][i] = 0;
                    s->sb_samples[1][k * 12 + l + 1][i] = 0;
                    s->sb_samples[1][k * 12 + l + 2][i] = 0;
                }
                /* next subband in alloc table */
                j += 1 << bit_alloc_bits;
            }
            /* fill remaining samples to zero */
            for (i = sblimit; i < SBLIMIT; i++) {
                for (ch = 0; ch < s->nb_channels; ch++) {
                    s->sb_samples[ch][k * 12 + l + 0][i] = 0;
                    s->sb_samples[ch][k * 12 + l + 1][i] = 0;
                    s->sb_samples[ch][k * 12 + l + 2][i] = 0;
                }
            }
        }
    }
    return 3 * 12;
}