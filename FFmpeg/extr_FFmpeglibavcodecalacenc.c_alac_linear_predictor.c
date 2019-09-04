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
typedef  int int32_t ;
struct TYPE_5__ {int** predictor_buf; int** sample_buf; int frame_size; int /*<<< orphan*/  write_sample_size; TYPE_1__* lpc; } ;
struct TYPE_4__ {int lpc_order; int lpc_quant; int* lpc_coeff; } ;
typedef  TYPE_1__ AlacLPCContext ;
typedef  TYPE_2__ AlacEncodeContext ;

/* Variables and functions */
 int FFSIGN (int) ; 
 int sign_extend (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alac_linear_predictor(AlacEncodeContext *s, int ch)
{
    int i;
    AlacLPCContext lpc = s->lpc[ch];
    int32_t *residual = s->predictor_buf[ch];

    if (lpc.lpc_order == 31) {
        residual[0] = s->sample_buf[ch][0];

        for (i = 1; i < s->frame_size; i++) {
            residual[i] = s->sample_buf[ch][i    ] -
                          s->sample_buf[ch][i - 1];
        }

        return;
    }

    // generalised linear predictor

    if (lpc.lpc_order > 0) {
        int32_t *samples  = s->sample_buf[ch];

        // generate warm-up samples
        residual[0] = samples[0];
        for (i = 1; i <= lpc.lpc_order; i++)
            residual[i] = sign_extend(samples[i] - samples[i-1], s->write_sample_size);

        // perform lpc on remaining samples
        for (i = lpc.lpc_order + 1; i < s->frame_size; i++) {
            int sum = 1 << (lpc.lpc_quant - 1), res_val, j;

            for (j = 0; j < lpc.lpc_order; j++) {
                sum += (samples[lpc.lpc_order-j] - samples[0]) *
                       lpc.lpc_coeff[j];
            }

            sum >>= lpc.lpc_quant;
            sum += samples[0];
            residual[i] = sign_extend(samples[lpc.lpc_order+1] - sum,
                                      s->write_sample_size);
            res_val = residual[i];

            if (res_val) {
                int index = lpc.lpc_order - 1;
                int neg = (res_val < 0);

                while (index >= 0 && (neg ? (res_val < 0) : (res_val > 0))) {
                    int val  = samples[0] - samples[lpc.lpc_order - index];
                    int sign = (val ? FFSIGN(val) : 0);

                    if (neg)
                        sign *= -1;

                    lpc.lpc_coeff[index] -= sign;
                    val *= sign;
                    res_val -= (val >> lpc.lpc_quant) * (lpc.lpc_order - index);
                    index--;
                }
            }
            samples++;
        }
    }
}