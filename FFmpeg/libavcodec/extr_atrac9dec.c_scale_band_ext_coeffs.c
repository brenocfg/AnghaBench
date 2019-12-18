#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float* coeffs; } ;
typedef  TYPE_1__ ATRAC9ChannelData ;

/* Variables and functions */
 int* at9_q_unit_to_coeff_idx ; 

__attribute__((used)) static inline void scale_band_ext_coeffs(ATRAC9ChannelData *c, float sf[6],
                                         const int s_unit, const int e_unit)
{
    for (int i = s_unit; i < e_unit; i++) {
        const int start = at9_q_unit_to_coeff_idx[i + 0];
        const int end   = at9_q_unit_to_coeff_idx[i + 1];
        for (int j = start; j < end; j++)
            c->coeffs[j] *= sf[i - s_unit];
    }
}