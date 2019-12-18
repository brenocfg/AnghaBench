#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int scalefac_compress; int short_start; int long_end; int* scale_factors; scalar_t__* sb_hybrid; } ;
struct TYPE_8__ {int mode_ext; size_t sample_rate_index; TYPE_1__* fdsp; int /*<<< orphan*/  lsf; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* butterflies_float ) (scalar_t__*,scalar_t__*,int) ;} ;
typedef  scalar_t__ SUINTFLOAT ;
typedef  TYPE_2__ MPADecodeContext ;
typedef  scalar_t__ INTFLOAT ;
typedef  TYPE_3__ GranuleDef ;

/* Variables and functions */
 int /*<<< orphan*/  FRAC_BITS ; 
 scalar_t__ ISQRT2 ; 
 int MODE_EXT_I_STEREO ; 
 int MODE_EXT_MS_STEREO ; 
 scalar_t__ MULLx (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int** band_size_long ; 
 int** band_size_short ; 
 scalar_t__** is_table ; 
 scalar_t__*** is_table_lsf ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void compute_stereo(MPADecodeContext *s, GranuleDef *g0, GranuleDef *g1)
{
    int i, j, k, l;
    int sf_max, sf, len, non_zero_found;
    INTFLOAT (*is_tab)[16], *tab0, *tab1, v1, v2;
    SUINTFLOAT tmp0, tmp1;
    int non_zero_found_short[3];

    /* intensity stereo */
    if (s->mode_ext & MODE_EXT_I_STEREO) {
        if (!s->lsf) {
            is_tab = is_table;
            sf_max = 7;
        } else {
            is_tab = is_table_lsf[g1->scalefac_compress & 1];
            sf_max = 16;
        }

        tab0 = g0->sb_hybrid + 576;
        tab1 = g1->sb_hybrid + 576;

        non_zero_found_short[0] = 0;
        non_zero_found_short[1] = 0;
        non_zero_found_short[2] = 0;
        k = (13 - g1->short_start) * 3 + g1->long_end - 3;
        for (i = 12; i >= g1->short_start; i--) {
            /* for last band, use previous scale factor */
            if (i != 11)
                k -= 3;
            len = band_size_short[s->sample_rate_index][i];
            for (l = 2; l >= 0; l--) {
                tab0 -= len;
                tab1 -= len;
                if (!non_zero_found_short[l]) {
                    /* test if non zero band. if so, stop doing i-stereo */
                    for (j = 0; j < len; j++) {
                        if (tab1[j] != 0) {
                            non_zero_found_short[l] = 1;
                            goto found1;
                        }
                    }
                    sf = g1->scale_factors[k + l];
                    if (sf >= sf_max)
                        goto found1;

                    v1 = is_tab[0][sf];
                    v2 = is_tab[1][sf];
                    for (j = 0; j < len; j++) {
                        tmp0    = tab0[j];
                        tab0[j] = MULLx(tmp0, v1, FRAC_BITS);
                        tab1[j] = MULLx(tmp0, v2, FRAC_BITS);
                    }
                } else {
found1:
                    if (s->mode_ext & MODE_EXT_MS_STEREO) {
                        /* lower part of the spectrum : do ms stereo
                           if enabled */
                        for (j = 0; j < len; j++) {
                            tmp0    = tab0[j];
                            tmp1    = tab1[j];
                            tab0[j] = MULLx(tmp0 + tmp1, ISQRT2, FRAC_BITS);
                            tab1[j] = MULLx(tmp0 - tmp1, ISQRT2, FRAC_BITS);
                        }
                    }
                }
            }
        }

        non_zero_found = non_zero_found_short[0] |
                         non_zero_found_short[1] |
                         non_zero_found_short[2];

        for (i = g1->long_end - 1;i >= 0;i--) {
            len   = band_size_long[s->sample_rate_index][i];
            tab0 -= len;
            tab1 -= len;
            /* test if non zero band. if so, stop doing i-stereo */
            if (!non_zero_found) {
                for (j = 0; j < len; j++) {
                    if (tab1[j] != 0) {
                        non_zero_found = 1;
                        goto found2;
                    }
                }
                /* for last band, use previous scale factor */
                k  = (i == 21) ? 20 : i;
                sf = g1->scale_factors[k];
                if (sf >= sf_max)
                    goto found2;
                v1 = is_tab[0][sf];
                v2 = is_tab[1][sf];
                for (j = 0; j < len; j++) {
                    tmp0    = tab0[j];
                    tab0[j] = MULLx(tmp0, v1, FRAC_BITS);
                    tab1[j] = MULLx(tmp0, v2, FRAC_BITS);
                }
            } else {
found2:
                if (s->mode_ext & MODE_EXT_MS_STEREO) {
                    /* lower part of the spectrum : do ms stereo
                       if enabled */
                    for (j = 0; j < len; j++) {
                        tmp0    = tab0[j];
                        tmp1    = tab1[j];
                        tab0[j] = MULLx(tmp0 + tmp1, ISQRT2, FRAC_BITS);
                        tab1[j] = MULLx(tmp0 - tmp1, ISQRT2, FRAC_BITS);
                    }
                }
            }
        }
    } else if (s->mode_ext & MODE_EXT_MS_STEREO) {
        /* ms stereo ONLY */
        /* NOTE: the 1/sqrt(2) normalization factor is included in the
           global gain */
#if USE_FLOATS
       s->fdsp->butterflies_float(g0->sb_hybrid, g1->sb_hybrid, 576);
#else
        tab0 = g0->sb_hybrid;
        tab1 = g1->sb_hybrid;
        for (i = 0; i < 576; i++) {
            tmp0    = tab0[i];
            tmp1    = tab1[i];
            tab0[i] = tmp0 + tmp1;
            tab1[i] = tmp0 - tmp1;
        }
#endif
    }
}