#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int global_gain; int scalefac_scale; size_t preflag; int long_end; int const* scale_factors; int short_start; int* subblock_gain; } ;
struct TYPE_5__ {size_t sample_rate_index; } ;
typedef  TYPE_1__ MPADecodeContext ;
typedef  TYPE_2__ GranuleDef ;

/* Variables and functions */
 int** band_size_long ; 
 int** band_size_short ; 
 int** mpa_pretab ; 

__attribute__((used)) static void exponents_from_scale_factors(MPADecodeContext *s, GranuleDef *g,
                                         int16_t *exponents)
{
    const uint8_t *bstab, *pretab;
    int len, i, j, k, l, v0, shift, gain, gains[3];
    int16_t *exp_ptr;

    exp_ptr = exponents;
    gain    = g->global_gain - 210;
    shift   = g->scalefac_scale + 1;

    bstab  = band_size_long[s->sample_rate_index];
    pretab = mpa_pretab[g->preflag];
    for (i = 0; i < g->long_end; i++) {
        v0 = gain - ((g->scale_factors[i] + pretab[i]) << shift) + 400;
        len = bstab[i];
        for (j = len; j > 0; j--)
            *exp_ptr++ = v0;
    }

    if (g->short_start < 13) {
        bstab    = band_size_short[s->sample_rate_index];
        gains[0] = gain - (g->subblock_gain[0] << 3);
        gains[1] = gain - (g->subblock_gain[1] << 3);
        gains[2] = gain - (g->subblock_gain[2] << 3);
        k        = g->long_end;
        for (i = g->short_start; i < 13; i++) {
            len = bstab[i];
            for (l = 0; l < 3; l++) {
                v0 = gains[l] - (g->scale_factors[k++] << shift) + 400;
                for (j = len; j > 0; j--)
                    *exp_ptr++ = v0;
            }
        }
    }
}