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
typedef  int int64_t ;
typedef  unsigned int int32_t ;
struct TYPE_10__ {unsigned int** msb_sample_buffer; int* adapt_pred_order; int** adapt_refl_coeff; int* fixed_pred_order; int* decor_coeff; size_t* orig_order; scalar_t__ decor_enabled; } ;
struct TYPE_9__ {int nchannels; int nfreqbands; size_t* ch_remap; TYPE_4__* bands; } ;
struct TYPE_8__ {int nframesamples; unsigned int** output_samples; TYPE_1__* dcadsp; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* decor ) (unsigned int*,unsigned int*,int,int) ;} ;
typedef  unsigned int SUINT ;
typedef  TYPE_2__ DCAXllDecoder ;
typedef  TYPE_3__ DCAXllChSet ;
typedef  TYPE_4__ DCAXllBand ;

/* Variables and functions */
 int DCA_XLL_ADAPT_PRED_ORDER_MAX ; 
 int DCA_XLL_CHANNELS_MAX ; 
 scalar_t__ clip23 (int /*<<< orphan*/ ) ; 
 int mul16 (int,int) ; 
 int /*<<< orphan*/  norm16 (int) ; 
 int /*<<< orphan*/  stub1 (unsigned int*,unsigned int*,int,int) ; 

__attribute__((used)) static void chs_filter_band_data(DCAXllDecoder *s, DCAXllChSet *c, int band)
{
    DCAXllBand *b = &c->bands[band];
    int nsamples = s->nframesamples;
    int i, j, k;

    // Inverse adaptive or fixed prediction
    for (i = 0; i < c->nchannels; i++) {
        int32_t *buf = b->msb_sample_buffer[i];
        int order = b->adapt_pred_order[i];
        if (order > 0) {
            int coeff[DCA_XLL_ADAPT_PRED_ORDER_MAX];
            // Conversion from reflection coefficients to direct form coefficients
            for (j = 0; j < order; j++) {
                int rc = b->adapt_refl_coeff[i][j];
                for (k = 0; k < (j + 1) / 2; k++) {
                    int tmp1 = coeff[    k    ];
                    int tmp2 = coeff[j - k - 1];
                    coeff[    k    ] = tmp1 + mul16(rc, tmp2);
                    coeff[j - k - 1] = tmp2 + mul16(rc, tmp1);
                }
                coeff[j] = rc;
            }
            // Inverse adaptive prediction
            for (j = 0; j < nsamples - order; j++) {
                int64_t err = 0;
                for (k = 0; k < order; k++)
                    err += (int64_t)buf[j + k] * coeff[order - k - 1];
                buf[j + k] -= (SUINT)clip23(norm16(err));
            }
        } else {
            // Inverse fixed coefficient prediction
            for (j = 0; j < b->fixed_pred_order[i]; j++)
                for (k = 1; k < nsamples; k++)
                    buf[k] += (unsigned)buf[k - 1];
        }
    }

    // Inverse pairwise channel decorrellation
    if (b->decor_enabled) {
        int32_t *tmp[DCA_XLL_CHANNELS_MAX];

        for (i = 0; i < c->nchannels / 2; i++) {
            int coeff = b->decor_coeff[i];
            if (coeff) {
                s->dcadsp->decor(b->msb_sample_buffer[i * 2 + 1],
                                 b->msb_sample_buffer[i * 2    ],
                                 coeff, nsamples);
            }
        }

        // Reorder channel pointers to the original order
        for (i = 0; i < c->nchannels; i++)
            tmp[i] = b->msb_sample_buffer[i];

        for (i = 0; i < c->nchannels; i++)
            b->msb_sample_buffer[b->orig_order[i]] = tmp[i];
    }

    // Map output channel pointers for frequency band 0
    if (c->nfreqbands == 1)
        for (i = 0; i < c->nchannels; i++)
            s->output_samples[c->ch_remap[i]] = b->msb_sample_buffer[i];
}