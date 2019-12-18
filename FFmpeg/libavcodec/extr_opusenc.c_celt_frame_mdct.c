#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  (* mdct ) (TYPE_5__*,float*,float*,int) ;} ;
struct TYPE_12__ {float* overlap; float* samples; float* coeffs; float* lin_energy; scalar_t__* energy; } ;
struct TYPE_11__ {int channels; int blocks; int size; TYPE_4__* block; scalar_t__ transient; } ;
struct TYPE_10__ {float* scratch; TYPE_5__** mdct; TYPE_1__* dsp; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* vector_fmul_reverse ) (float*,float*,scalar_t__,int) ;int /*<<< orphan*/  (* vector_fmul ) (float*,float*,scalar_t__,int) ;} ;
typedef  TYPE_2__ OpusEncContext ;
typedef  TYPE_3__ CeltFrame ;
typedef  TYPE_4__ CeltBlock ;

/* Variables and functions */
 int /*<<< orphan*/  CELT_ENERGY_SILENCE ; 
 int CELT_MAX_BANDS ; 
 int CELT_OVERLAP ; 
 scalar_t__ FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 
 float FLT_EPSILON ; 
 int OPUS_BLOCK_SIZE (int) ; 
 int* ff_celt_freq_bands ; 
 int* ff_celt_freq_range ; 
 scalar_t__* ff_celt_mean_energy ; 
 scalar_t__ ff_celt_window ; 
 scalar_t__ log2f (float) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 float sqrtf (float) ; 
 int /*<<< orphan*/  stub1 (float*,float*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,float*,float*,int) ; 
 int /*<<< orphan*/  stub4 (float*,float*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub5 (float*,float*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_5__*,float*,float*,int) ; 

__attribute__((used)) static void celt_frame_mdct(OpusEncContext *s, CeltFrame *f)
{
    float *win = s->scratch, *temp = s->scratch + 1920;

    if (f->transient) {
        for (int ch = 0; ch < f->channels; ch++) {
            CeltBlock *b = &f->block[ch];
            float *src1 = b->overlap;
            for (int t = 0; t < f->blocks; t++) {
                float *src2 = &b->samples[CELT_OVERLAP*t];
                s->dsp->vector_fmul(win, src1, ff_celt_window, 128);
                s->dsp->vector_fmul_reverse(&win[CELT_OVERLAP], src2,
                                            ff_celt_window - 8, 128);
                src1 = src2;
                s->mdct[0]->mdct(s->mdct[0], b->coeffs + t, win, f->blocks);
            }
        }
    } else {
        int blk_len = OPUS_BLOCK_SIZE(f->size), wlen = OPUS_BLOCK_SIZE(f->size + 1);
        int rwin = blk_len - CELT_OVERLAP, lap_dst = (wlen - blk_len - CELT_OVERLAP) >> 1;
        memset(win, 0, wlen*sizeof(float));
        for (int ch = 0; ch < f->channels; ch++) {
            CeltBlock *b = &f->block[ch];

            /* Overlap */
            s->dsp->vector_fmul(temp, b->overlap, ff_celt_window, 128);
            memcpy(win + lap_dst, temp, CELT_OVERLAP*sizeof(float));

            /* Samples, flat top window */
            memcpy(&win[lap_dst + CELT_OVERLAP], b->samples, rwin*sizeof(float));

            /* Samples, windowed */
            s->dsp->vector_fmul_reverse(temp, b->samples + rwin,
                                        ff_celt_window - 8, 128);
            memcpy(win + lap_dst + blk_len, temp, CELT_OVERLAP*sizeof(float));

            s->mdct[f->size]->mdct(s->mdct[f->size], b->coeffs, win, 1);
        }
    }

    for (int ch = 0; ch < f->channels; ch++) {
        CeltBlock *block = &f->block[ch];
        for (int i = 0; i < CELT_MAX_BANDS; i++) {
            float ener = 0.0f;
            int band_offset = ff_celt_freq_bands[i] << f->size;
            int band_size   = ff_celt_freq_range[i] << f->size;
            float *coeffs   = &block->coeffs[band_offset];

            for (int j = 0; j < band_size; j++)
                ener += coeffs[j]*coeffs[j];

            block->lin_energy[i] = sqrtf(ener) + FLT_EPSILON;
            ener = 1.0f/block->lin_energy[i];

            for (int j = 0; j < band_size; j++)
                coeffs[j] *= ener;

            block->energy[i] = log2f(block->lin_energy[i]) - ff_celt_mean_energy[i];

            /* CELT_ENERGY_SILENCE is what the decoder uses and its not -infinity */
            block->energy[i] = FFMAX(block->energy[i], CELT_ENERGY_SILENCE);
        }
    }
}