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

/* Variables and functions */
 int quant_array_idx (double,float const*,int) ; 
 float** tns_tmp2_map ; 

__attribute__((used)) static inline void quantize_coefs(double *coef, int *idx, float *lpc, int order,
                                  int c_bits)
{
    int i;
    const float *quant_arr = tns_tmp2_map[c_bits];
    for (i = 0; i < order; i++) {
        idx[i] = quant_array_idx(coef[i], quant_arr, c_bits ? 16 : 8);
        lpc[i] = quant_arr[idx[i]];
    }
}