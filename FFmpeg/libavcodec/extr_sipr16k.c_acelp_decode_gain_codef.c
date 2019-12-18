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
 int M_LN10 ; 
 scalar_t__ avpriv_scalarproduct_float_c (float const*,float const*,int) ; 
 float exp (int) ; 
 float sqrt (scalar_t__) ; 

__attribute__((used)) static float acelp_decode_gain_codef(float gain_corr_factor, const float *fc_v,
                                     float mr_energy, const float *quant_energy,
                                     const float *ma_prediction_coeff,
                                     int subframe_size, int ma_pred_order)
{
    mr_energy += avpriv_scalarproduct_float_c(quant_energy, ma_prediction_coeff,
                                              ma_pred_order);

    mr_energy = gain_corr_factor * exp(M_LN10 / 20. * mr_energy) /
        sqrt((0.01 + avpriv_scalarproduct_float_c(fc_v, fc_v, subframe_size)));
    return mr_energy;
}