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
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_3__ {int slow_gain; int fast_decay; int slow_decay; int cpl_fast_leak; int cpl_slow_leak; int db_per_bit; int sr_shift; size_t sr_code; } ;
typedef  TYPE_1__ AC3BitAllocParameters ;

/* Variables and functions */
 int AC3_CRITICAL_BANDS ; 
 int AVERROR_INVALIDDATA ; 
 int DBA_NEW ; 
 int DBA_REUSE ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int calc_lowcomp (int,int,int,int) ; 
 int calc_lowcomp1 (int,int,int,int) ; 
 int* ff_ac3_bin_to_band_tab ; 
 int** ff_ac3_hearing_threshold_tab ; 

int ff_ac3_bit_alloc_calc_mask(AC3BitAllocParameters *s, int16_t *band_psd,
                               int start, int end, int fast_gain, int is_lfe,
                               int dba_mode, int dba_nsegs, uint8_t *dba_offsets,
                               uint8_t *dba_lengths, uint8_t *dba_values,
                               int16_t *mask)
{
    int16_t excite[AC3_CRITICAL_BANDS]; /* excitation */
    int band;
    int band_start, band_end, begin, end1;
    int lowcomp, fastleak, slowleak;

    if (end <= 0)
        return AVERROR_INVALIDDATA;

    /* excitation function */
    band_start = ff_ac3_bin_to_band_tab[start];
    band_end   = ff_ac3_bin_to_band_tab[end-1] + 1;

    if (band_start == 0) {
        lowcomp = 0;
        lowcomp = calc_lowcomp1(lowcomp, band_psd[0], band_psd[1], 384);
        excite[0] = band_psd[0] - fast_gain - lowcomp;
        lowcomp = calc_lowcomp1(lowcomp, band_psd[1], band_psd[2], 384);
        excite[1] = band_psd[1] - fast_gain - lowcomp;
        begin = 7;
        for (band = 2; band < 7; band++) {
            if (!(is_lfe && band == 6))
                lowcomp = calc_lowcomp1(lowcomp, band_psd[band], band_psd[band+1], 384);
            fastleak = band_psd[band] - fast_gain;
            slowleak = band_psd[band] - s->slow_gain;
            excite[band] = fastleak - lowcomp;
            if (!(is_lfe && band == 6)) {
                if (band_psd[band] <= band_psd[band+1]) {
                    begin = band + 1;
                    break;
                }
            }
        }

        end1 = FFMIN(band_end, 22);
        for (band = begin; band < end1; band++) {
            if (!(is_lfe && band == 6))
                lowcomp = calc_lowcomp(lowcomp, band_psd[band], band_psd[band+1], band);
            fastleak = FFMAX(fastleak - s->fast_decay, band_psd[band] - fast_gain);
            slowleak = FFMAX(slowleak - s->slow_decay, band_psd[band] - s->slow_gain);
            excite[band] = FFMAX(fastleak - lowcomp, slowleak);
        }
        begin = 22;
    } else {
        /* coupling channel */
        begin = band_start;
        fastleak = (s->cpl_fast_leak << 8) + 768;
        slowleak = (s->cpl_slow_leak << 8) + 768;
    }

    for (band = begin; band < band_end; band++) {
        fastleak = FFMAX(fastleak - s->fast_decay, band_psd[band] - fast_gain);
        slowleak = FFMAX(slowleak - s->slow_decay, band_psd[band] - s->slow_gain);
        excite[band] = FFMAX(fastleak, slowleak);
    }

    /* compute masking curve */

    for (band = band_start; band < band_end; band++) {
        int tmp = s->db_per_bit - band_psd[band];
        if (tmp > 0) {
            excite[band] += tmp >> 2;
        }
        mask[band] = FFMAX(ff_ac3_hearing_threshold_tab[band >> s->sr_shift][s->sr_code], excite[band]);
    }

    /* delta bit allocation */

    if (dba_mode == DBA_REUSE || dba_mode == DBA_NEW) {
        int i, seg, delta;
        if (dba_nsegs > 8)
            return -1;
        band = band_start;
        for (seg = 0; seg < dba_nsegs; seg++) {
            band += dba_offsets[seg];
            if (band >= AC3_CRITICAL_BANDS || dba_lengths[seg] > AC3_CRITICAL_BANDS-band)
                return -1;
            if (dba_values[seg] >= 4) {
                delta = (dba_values[seg] - 3) * 128;
            } else {
                delta = (dba_values[seg] - 4) * 128;
            }
            for (i = 0; i < dba_lengths[seg]; i++) {
                mask[band++] += delta;
            }
        }
    }
    return 0;
}