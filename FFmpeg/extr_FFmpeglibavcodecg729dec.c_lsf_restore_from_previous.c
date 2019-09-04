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
typedef  int int16_t ;

/* Variables and functions */
 size_t MA_NP ; 
 int*** cb_ma_predictor ; 
 int** cb_ma_predictor_sum_inv ; 

__attribute__((used)) static void lsf_restore_from_previous(int16_t* lsfq,
                                      int16_t* past_quantizer_outputs[MA_NP + 1],
                                      int ma_predictor_prev)
{
    int16_t* quantizer_output = past_quantizer_outputs[MA_NP];
    int i,k;

    for (i = 0; i < 10; i++) {
        int tmp = lsfq[i] << 15;

        for (k = 0; k < MA_NP; k++)
            tmp -= past_quantizer_outputs[k][i] * cb_ma_predictor[ma_predictor_prev][k][i];

        quantizer_output[i] = ((tmp >> 15) * cb_ma_predictor_sum_inv[ma_predictor_prev][i]) >> 12;
    }
}