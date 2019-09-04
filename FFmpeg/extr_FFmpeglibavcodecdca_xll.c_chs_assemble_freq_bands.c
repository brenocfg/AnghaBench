#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {int nfreqbands; int nchannels; size_t* ch_remap; int /*<<< orphan*/ * deci_history; TYPE_1__* bands; int /*<<< orphan*/ ** sample_buffer; int /*<<< orphan*/ * sample_size; } ;
struct TYPE_9__ {int nframesamples; int /*<<< orphan*/ ** output_samples; TYPE_2__* dcadsp; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* assemble_freq_bands ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/ ** msb_sample_buffer; } ;
typedef  TYPE_3__ DCAXllDecoder ;
typedef  TYPE_4__ DCAXllChSet ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int DCA_XLL_DECI_HISTORY_MAX ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_dca_xll_band_coeff ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int chs_assemble_freq_bands(DCAXllDecoder *s, DCAXllChSet *c)
{
    int ch, nsamples = s->nframesamples;
    int32_t *ptr;

    av_assert1(c->nfreqbands > 1);

    // Reallocate frequency band assembly buffer
    av_fast_malloc(&c->sample_buffer[2], &c->sample_size[2],
                   2 * nsamples * c->nchannels * sizeof(int32_t));
    if (!c->sample_buffer[2])
        return AVERROR(ENOMEM);

    // Assemble frequency bands 0 and 1
    ptr = c->sample_buffer[2];
    for (ch = 0; ch < c->nchannels; ch++) {
        int32_t *band0 = c->bands[0].msb_sample_buffer[ch];
        int32_t *band1 = c->bands[1].msb_sample_buffer[ch];

        // Copy decimator history
        memcpy(band0 - DCA_XLL_DECI_HISTORY_MAX,
               c->deci_history[ch], sizeof(c->deci_history[0]));

        // Filter
        s->dcadsp->assemble_freq_bands(ptr, band0, band1,
                                       ff_dca_xll_band_coeff,
                                       nsamples);

        // Remap output channel pointer to assembly buffer
        s->output_samples[c->ch_remap[ch]] = ptr;
        ptr += nsamples * 2;
    }

    return 0;
}