#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* lspv; } ;
struct TYPE_5__ {scalar_t__ bitrate; scalar_t__ prev_bitrate; float* prev_lspf; float* predictor_lspf; int octave_count; int erasure_count; TYPE_1__ frame; } ;
typedef  TYPE_2__ QCELPContext ;

/* Variables and functions */
 float FFMAX (float,float const) ; 
 float FFMIN (float,float) ; 
 scalar_t__ I_F_Q ; 
 float const QCELP_LSP_OCTAVE_PREDICTOR ; 
 float const QCELP_LSP_SPREAD_FACTOR ; 
 scalar_t__ RATE_OCTAVE ; 
 scalar_t__ RATE_QUARTER ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 double fabs (float) ; 
 int /*<<< orphan*/  ff_weighted_vector_sumf (float*,float*,float*,float,double,int) ; 
 double*** qcelp_lspvq ; 

__attribute__((used)) static int decode_lspf(QCELPContext *q, float *lspf)
{
    int i;
    float tmp_lspf, smooth, erasure_coeff;
    const float *predictors;

    if (q->bitrate == RATE_OCTAVE || q->bitrate == I_F_Q) {
        predictors = q->prev_bitrate != RATE_OCTAVE &&
                     q->prev_bitrate != I_F_Q ? q->prev_lspf
                                              : q->predictor_lspf;

        if (q->bitrate == RATE_OCTAVE) {
            q->octave_count++;

            for (i = 0; i < 10; i++) {
                q->predictor_lspf[i] =
                             lspf[i] = (q->frame.lspv[i] ?  QCELP_LSP_SPREAD_FACTOR
                                                         : -QCELP_LSP_SPREAD_FACTOR) +
                                        predictors[i] * QCELP_LSP_OCTAVE_PREDICTOR   +
                                        (i + 1) * ((1 - QCELP_LSP_OCTAVE_PREDICTOR) / 11);
            }
            smooth = q->octave_count < 10 ? .875 : 0.1;
        } else {
            erasure_coeff = QCELP_LSP_OCTAVE_PREDICTOR;

            av_assert2(q->bitrate == I_F_Q);

            if (q->erasure_count > 1)
                erasure_coeff *= q->erasure_count < 4 ? 0.9 : 0.7;

            for (i = 0; i < 10; i++) {
                q->predictor_lspf[i] =
                             lspf[i] = (i + 1) * (1 - erasure_coeff) / 11 +
                                       erasure_coeff * predictors[i];
            }
            smooth = 0.125;
        }

        // Check the stability of the LSP frequencies.
        lspf[0] = FFMAX(lspf[0], QCELP_LSP_SPREAD_FACTOR);
        for (i = 1; i < 10; i++)
            lspf[i] = FFMAX(lspf[i], lspf[i - 1] + QCELP_LSP_SPREAD_FACTOR);

        lspf[9] = FFMIN(lspf[9], 1.0 - QCELP_LSP_SPREAD_FACTOR);
        for (i = 9; i > 0; i--)
            lspf[i - 1] = FFMIN(lspf[i - 1], lspf[i] - QCELP_LSP_SPREAD_FACTOR);

        // Low-pass filter the LSP frequencies.
        ff_weighted_vector_sumf(lspf, lspf, q->prev_lspf, smooth, 1.0 - smooth, 10);
    } else {
        q->octave_count = 0;

        tmp_lspf = 0.0;
        for (i = 0; i < 5; i++) {
            lspf[2 * i + 0] = tmp_lspf += qcelp_lspvq[i][q->frame.lspv[i]][0] * 0.0001;
            lspf[2 * i + 1] = tmp_lspf += qcelp_lspvq[i][q->frame.lspv[i]][1] * 0.0001;
        }

        // Check for badly received packets.
        if (q->bitrate == RATE_QUARTER) {
            if (lspf[9] <= .70 || lspf[9] >= .97)
                return -1;
            for (i = 3; i < 10; i++)
                if (fabs(lspf[i] - lspf[i - 2]) < .08)
                    return -1;
        } else {
            if (lspf[9] <= .66 || lspf[9] >= .985)
                return -1;
            for (i = 4; i < 10; i++)
                if (fabs(lspf[i] - lspf[i - 4]) < .0931)
                    return -1;
        }
    }
    return 0;
}