#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int (* quant_band ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,float*,float*,int,int,int,float*,int,float*,int /*<<< orphan*/ ,float,float*,int) ;} ;
struct TYPE_11__ {int framebits; int anticollapse_needed; int start_band; int end_band; int blocks; int size; int channels; int remaining; int remaining2; int coded_bands; int* pulses; scalar_t__ spread; scalar_t__* tf_change; int intensity_stereo; TYPE_1__* block; TYPE_3__* pvq; scalar_t__ dual_stereo; } ;
struct TYPE_10__ {float* coeffs; int* collapse_masks; } ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_2__ CeltFrame ;

/* Variables and functions */
 scalar_t__ CELT_SPREAD_AGGRESSIVE ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int av_clip_uintp2 (int,int) ; 
 int* ff_celt_freq_bands ; 
 int* ff_celt_freq_range ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int opus_rc_tell_frac (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,float*,float*,int,int,int,float*,int,float*,int /*<<< orphan*/ ,float,float*,int) ; 
 int stub2 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,float*,float*,int,int,int,float*,int,float*,int /*<<< orphan*/ ,float,float*,int) ; 
 int stub3 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,float*,float*,int,int,int,float*,int,float*,int /*<<< orphan*/ ,float,float*,int) ; 

void ff_celt_quant_bands(CeltFrame *f, OpusRangeCoder *rc)
{
    float lowband_scratch[8 * 22];
    float norm1[2 * 8 * 100];
    float *norm2 = norm1 + 8 * 100;

    int totalbits = (f->framebits << 3) - f->anticollapse_needed;

    int update_lowband = 1;
    int lowband_offset = 0;

    int i, j;

    for (i = f->start_band; i < f->end_band; i++) {
        uint32_t cm[2] = { (1 << f->blocks) - 1, (1 << f->blocks) - 1 };
        int band_offset = ff_celt_freq_bands[i] << f->size;
        int band_size   = ff_celt_freq_range[i] << f->size;
        float *X = f->block[0].coeffs + band_offset;
        float *Y = (f->channels == 2) ? f->block[1].coeffs + band_offset : NULL;
        float *norm_loc1, *norm_loc2;

        int consumed = opus_rc_tell_frac(rc);
        int effective_lowband = -1;
        int b = 0;

        /* Compute how many bits we want to allocate to this band */
        if (i != f->start_band)
            f->remaining -= consumed;
        f->remaining2 = totalbits - consumed - 1;
        if (i <= f->coded_bands - 1) {
            int curr_balance = f->remaining / FFMIN(3, f->coded_bands-i);
            b = av_clip_uintp2(FFMIN(f->remaining2 + 1, f->pulses[i] + curr_balance), 14);
        }

        if ((ff_celt_freq_bands[i] - ff_celt_freq_range[i] >= ff_celt_freq_bands[f->start_band] ||
            i == f->start_band + 1) && (update_lowband || lowband_offset == 0))
            lowband_offset = i;

        if (i == f->start_band + 1) {
            /* Special Hybrid Folding (RFC 8251 section 9). Copy the first band into
            the second to ensure the second band never has to use the LCG. */
            int count = (ff_celt_freq_range[i] - ff_celt_freq_range[i-1]) << f->size;

            memcpy(&norm1[band_offset], &norm1[band_offset - count], count * sizeof(float));

            if (f->channels == 2)
                memcpy(&norm2[band_offset], &norm2[band_offset - count], count * sizeof(float));
        }

        /* Get a conservative estimate of the collapse_mask's for the bands we're
           going to be folding from. */
        if (lowband_offset != 0 && (f->spread != CELT_SPREAD_AGGRESSIVE ||
                                    f->blocks > 1 || f->tf_change[i] < 0)) {
            int foldstart, foldend;

            /* This ensures we never repeat spectral content within one band */
            effective_lowband = FFMAX(ff_celt_freq_bands[f->start_band],
                                      ff_celt_freq_bands[lowband_offset] - ff_celt_freq_range[i]);
            foldstart = lowband_offset;
            while (ff_celt_freq_bands[--foldstart] > effective_lowband);
            foldend = lowband_offset - 1;
            while (++foldend < i && ff_celt_freq_bands[foldend] < effective_lowband + ff_celt_freq_range[i]);

            cm[0] = cm[1] = 0;
            for (j = foldstart; j < foldend; j++) {
                cm[0] |= f->block[0].collapse_masks[j];
                cm[1] |= f->block[f->channels - 1].collapse_masks[j];
            }
        }

        if (f->dual_stereo && i == f->intensity_stereo) {
            /* Switch off dual stereo to do intensity */
            f->dual_stereo = 0;
            for (j = ff_celt_freq_bands[f->start_band] << f->size; j < band_offset; j++)
                norm1[j] = (norm1[j] + norm2[j]) / 2;
        }

        norm_loc1 = effective_lowband != -1 ? norm1 + (effective_lowband << f->size) : NULL;
        norm_loc2 = effective_lowband != -1 ? norm2 + (effective_lowband << f->size) : NULL;

        if (f->dual_stereo) {
            cm[0] = f->pvq->quant_band(f->pvq, f, rc, i, X, NULL, band_size, b >> 1,
                                       f->blocks, norm_loc1, f->size,
                                       norm1 + band_offset, 0, 1.0f,
                                       lowband_scratch, cm[0]);

            cm[1] = f->pvq->quant_band(f->pvq, f, rc, i, Y, NULL, band_size, b >> 1,
                                       f->blocks, norm_loc2, f->size,
                                       norm2 + band_offset, 0, 1.0f,
                                       lowband_scratch, cm[1]);
        } else {
            cm[0] = f->pvq->quant_band(f->pvq, f, rc, i, X,    Y, band_size, b >> 0,
                                       f->blocks, norm_loc1, f->size,
                                       norm1 + band_offset, 0, 1.0f,
                                       lowband_scratch, cm[0] | cm[1]);
            cm[1] = cm[0];
        }

        f->block[0].collapse_masks[i]               = (uint8_t)cm[0];
        f->block[f->channels - 1].collapse_masks[i] = (uint8_t)cm[1];
        f->remaining += f->pulses[i] + consumed;

        /* Update the folding position only as long as we have 1 bit/sample depth */
        update_lowband = (b > band_size << 3);
    }
}