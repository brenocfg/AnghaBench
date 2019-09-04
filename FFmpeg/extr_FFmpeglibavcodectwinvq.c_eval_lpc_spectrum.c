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

__attribute__((used)) static float eval_lpc_spectrum(const float *lsp, float cos_val, int order)
{
    int j;
    float p         = 0.5f;
    float q         = 0.5f;
    float two_cos_w = 2.0f * cos_val;

    for (j = 0; j + 1 < order; j += 2 * 2) {
        // Unroll the loop once since order is a multiple of four
        q *= lsp[j]     - two_cos_w;
        p *= lsp[j + 1] - two_cos_w;

        q *= lsp[j + 2] - two_cos_w;
        p *= lsp[j + 3] - two_cos_w;
    }

    p *= p * (2.0f - two_cos_w);
    q *= q * (2.0f + two_cos_w);

    return 0.5 / (p + q);
}