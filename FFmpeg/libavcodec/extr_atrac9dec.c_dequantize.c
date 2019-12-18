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
struct TYPE_3__ {float* coeffs; int q_unit_cnt; size_t* precision_coarse; size_t* precision_fine; float const* q_coeffs_coarse; float const* q_coeffs_fine; } ;
typedef  int /*<<< orphan*/  ATRAC9Context ;
typedef  TYPE_1__ ATRAC9ChannelData ;
typedef  int /*<<< orphan*/  ATRAC9BlockData ;

/* Variables and functions */
 int* at9_q_unit_to_coeff_idx ; 
 float* at9_quant_step_coarse ; 
 float* at9_quant_step_fine ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void dequantize(ATRAC9Context *s, ATRAC9BlockData *b,
                              ATRAC9ChannelData *c)
{
    memset(c->coeffs, 0, sizeof(c->coeffs));

    for (int i = 0; i < c->q_unit_cnt; i++) {
        const int start = at9_q_unit_to_coeff_idx[i + 0];
        const int end   = at9_q_unit_to_coeff_idx[i + 1];

        const float coarse_c = at9_quant_step_coarse[c->precision_coarse[i]];
        const float fine_c   = at9_quant_step_fine[c->precision_fine[i]];

        for (int j = start; j < end; j++) {
            const float vc = c->q_coeffs_coarse[j] * coarse_c;
            const float vf = c->q_coeffs_fine[j]   * fine_c;
            c->coeffs[j] = vc + vf;
        }
    }
}