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
 int FILTER_ORDER ; 

__attribute__((used)) static void synthesis_filter(const float *in, const float *filter_coeffs,
                             float *memory, int buffer_length, float *samples)
{
    int i, j;

    for (i = 0; i < buffer_length; i++) {
        samples[i] = in[i];
        for (j = FILTER_ORDER - 1; j > 0; j--) {
            samples[i] -= filter_coeffs[j] * memory[j];
            memory[j]   = memory[j - 1];
        }
        samples[i] -= filter_coeffs[0] * memory[0];
        memory[0]   = samples[i];
    }
}