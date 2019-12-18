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
 float avpriv_scalarproduct_float_c (float const*,float const*,int) ; 
 int /*<<< orphan*/  ff_scale_vector_to_given_sum_of_squares (float*,float const*,float,int) ; 

__attribute__((used)) static void apply_gain_ctrl(float *v_out, const float *v_ref, const float *v_in)
{
    int i;

    for (i = 0; i < 160; i += 40) {
        float res = avpriv_scalarproduct_float_c(v_ref + i, v_ref + i, 40);
        ff_scale_vector_to_given_sum_of_squares(v_out + i, v_in + i, res, 40);
    }
}