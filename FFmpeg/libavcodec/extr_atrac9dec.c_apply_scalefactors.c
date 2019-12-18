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
struct TYPE_5__ {int q_unit_cnt; TYPE_1__* channel; } ;
struct TYPE_4__ {float* coeffs; int* scalefactors; } ;
typedef  int /*<<< orphan*/  ATRAC9Context ;
typedef  TYPE_2__ ATRAC9BlockData ;

/* Variables and functions */
 int* at9_q_unit_to_coeff_idx ; 
 float* at9_scalefactor_c ; 

__attribute__((used)) static inline void apply_scalefactors(ATRAC9Context *s, ATRAC9BlockData *b,
                                      const int stereo)
{
    for (int i = 0; i <= stereo; i++) {
        float *coeffs = b->channel[i].coeffs;
        for (int j = 0; j < b->q_unit_cnt; j++) {
            const int start = at9_q_unit_to_coeff_idx[j + 0];
            const int end   = at9_q_unit_to_coeff_idx[j + 1];
            const int scalefactor = b->channel[i].scalefactors[j];
            const float scale = at9_scalefactor_c[scalefactor];
            for (int k = start; k < end; k++)
                coeffs[k] *= scale;
        }
    }
}