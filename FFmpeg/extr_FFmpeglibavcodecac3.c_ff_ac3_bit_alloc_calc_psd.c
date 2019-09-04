#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int8_t ;
typedef  int int16_t ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int* ff_ac3_band_start_tab ; 
 int* ff_ac3_bin_to_band_tab ; 
 int* ff_ac3_log_add_tab ; 

void ff_ac3_bit_alloc_calc_psd(int8_t *exp, int start, int end, int16_t *psd,
                               int16_t *band_psd)
{
    int bin, band;

    /* exponent mapping to PSD */
    for (bin = start; bin < end; bin++) {
        psd[bin]=(3072 - (exp[bin] << 7));
    }

    /* PSD integration */
    bin  = start;
    band = ff_ac3_bin_to_band_tab[start];
    do {
        int v = psd[bin++];
        int band_end = FFMIN(ff_ac3_band_start_tab[band+1], end);
        for (; bin < band_end; bin++) {
            int max = FFMAX(v, psd[bin]);
            /* logadd */
            int adr = FFMIN(max - ((v + psd[bin] + 1) >> 1), 255);
            v = max + ff_ac3_log_add_tab[adr];
        }
        band_psd[band++] = v;
    } while (end > ff_ac3_band_start_tab[band]);
}