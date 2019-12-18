#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* n_filt; int** order; scalar_t__** direction; int /*<<< orphan*/ ** coef; scalar_t__** length; } ;
typedef  TYPE_1__ TemporalNoiseShaping ;
struct TYPE_7__ {int tns_max_bands; int max_sfb; int num_windows; int num_swb; int* swb_offset; } ;
struct TYPE_6__ {float* coeffs; float* pcoeffs; TYPE_3__ ics; TYPE_1__ tns; } ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  AACEncContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int FFMIN (int,int const) ; 
 int TNS_MAX_ORDER ; 
 int /*<<< orphan*/  compute_lpc_coefs (int /*<<< orphan*/ ,int,float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_aac_apply_tns(AACEncContext *s, SingleChannelElement *sce)
{
    TemporalNoiseShaping *tns = &sce->tns;
    IndividualChannelStream *ics = &sce->ics;
    int w, filt, m, i, top, order, bottom, start, end, size, inc;
    const int mmm = FFMIN(ics->tns_max_bands, ics->max_sfb);
    float lpc[TNS_MAX_ORDER];

    for (w = 0; w < ics->num_windows; w++) {
        bottom = ics->num_swb;
        for (filt = 0; filt < tns->n_filt[w]; filt++) {
            top    = bottom;
            bottom = FFMAX(0, top - tns->length[w][filt]);
            order  = tns->order[w][filt];
            if (order == 0)
                continue;

            // tns_decode_coef
            compute_lpc_coefs(tns->coef[w][filt], order, lpc, 0, 0, 0);

            start = ics->swb_offset[FFMIN(bottom, mmm)];
            end   = ics->swb_offset[FFMIN(   top, mmm)];
            if ((size = end - start) <= 0)
                continue;
            if (tns->direction[w][filt]) {
                inc = -1;
                start = end - 1;
            } else {
                inc = 1;
            }
            start += w * 128;

            /* AR filter */
            for (m = 0; m < size; m++, start += inc) {
                for (i = 1; i <= FFMIN(m, order); i++) {
                    sce->coeffs[start] += lpc[i-1]*sce->pcoeffs[start - i*inc];
                }
            }
        }
    }
}