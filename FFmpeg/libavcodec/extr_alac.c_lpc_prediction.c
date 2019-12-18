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
typedef  int uint32_t ;
typedef  void* int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,void**,int) ; 
 int sign_extend (int,int) ; 
 int sign_only (int) ; 

__attribute__((used)) static void lpc_prediction(int32_t *error_buffer, uint32_t *buffer_out,
                           int nb_samples, int bps, int16_t *lpc_coefs,
                           int lpc_order, int lpc_quant)
{
    int i;
    uint32_t *pred = buffer_out;

    /* first sample always copies */
    *buffer_out = *error_buffer;

    if (nb_samples <= 1)
        return;

    if (!lpc_order) {
        memcpy(&buffer_out[1], &error_buffer[1],
               (nb_samples - 1) * sizeof(*buffer_out));
        return;
    }

    if (lpc_order == 31) {
        /* simple 1st-order prediction */
        for (i = 1; i < nb_samples; i++) {
            buffer_out[i] = sign_extend(buffer_out[i - 1] + error_buffer[i],
                                        bps);
        }
        return;
    }

    /* read warm-up samples */
    for (i = 1; i <= lpc_order && i < nb_samples; i++)
        buffer_out[i] = sign_extend(buffer_out[i - 1] + error_buffer[i], bps);

    /* NOTE: 4 and 8 are very common cases that could be optimized. */

    for (; i < nb_samples; i++) {
        int j;
        int val = 0;
        unsigned error_val = error_buffer[i];
        int error_sign;
        int d = *pred++;

        /* LPC prediction */
        for (j = 0; j < lpc_order; j++)
            val += (pred[j] - d) * lpc_coefs[j];
        val = (val + (1LL << (lpc_quant - 1))) >> lpc_quant;
        val += d + error_val;
        buffer_out[i] = sign_extend(val, bps);

        /* adapt LPC coefficients */
        error_sign = sign_only(error_val);
        if (error_sign) {
            for (j = 0; j < lpc_order && (int)(error_val * error_sign) > 0; j++) {
                int sign;
                val  = d - pred[j];
                sign = sign_only(val) * error_sign;
                lpc_coefs[j] -= sign;
                val *= sign;
                error_val -= (val >> lpc_quant) * (j + 1);
            }
        }
    }
}