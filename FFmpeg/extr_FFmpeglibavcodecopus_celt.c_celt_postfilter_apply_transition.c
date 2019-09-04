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
struct TYPE_3__ {int pf_period_old; int pf_period; double* pf_gains; double* pf_gains_old; } ;
typedef  TYPE_1__ CeltBlock ;

/* Variables and functions */
 int CELT_OVERLAP ; 
 float* ff_celt_window2 ; 

__attribute__((used)) static void celt_postfilter_apply_transition(CeltBlock *block, float *data)
{
    const int T0 = block->pf_period_old;
    const int T1 = block->pf_period;

    float g00, g01, g02;
    float g10, g11, g12;

    float x0, x1, x2, x3, x4;

    int i;

    if (block->pf_gains[0]     == 0.0 &&
        block->pf_gains_old[0] == 0.0)
        return;

    g00 = block->pf_gains_old[0];
    g01 = block->pf_gains_old[1];
    g02 = block->pf_gains_old[2];
    g10 = block->pf_gains[0];
    g11 = block->pf_gains[1];
    g12 = block->pf_gains[2];

    x1 = data[-T1 + 1];
    x2 = data[-T1];
    x3 = data[-T1 - 1];
    x4 = data[-T1 - 2];

    for (i = 0; i < CELT_OVERLAP; i++) {
        float w = ff_celt_window2[i];
        x0 = data[i - T1 + 2];

        data[i] +=  (1.0 - w) * g00 * data[i - T0]                          +
                    (1.0 - w) * g01 * (data[i - T0 - 1] + data[i - T0 + 1]) +
                    (1.0 - w) * g02 * (data[i - T0 - 2] + data[i - T0 + 2]) +
                    w         * g10 * x2                                    +
                    w         * g11 * (x1 + x3)                             +
                    w         * g12 * (x0 + x4);
        x4 = x3;
        x3 = x2;
        x2 = x1;
        x1 = x0;
    }
}