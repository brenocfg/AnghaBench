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

__attribute__((used)) static void residual_filter(float *output, const float *input,
                            const float *coef, float *memory, int length)
{
    float sum;
    int i, j;

    for (i = 0; i < length; i++) {
        sum = input[i];

        for (j = FILTER_ORDER - 1; j > 0; j--) {
            sum      += coef[j] * memory[j];
            memory[j] = memory[j - 1];
        }
        sum += coef[0] * memory[0];
        memory[0] = input[i];
        output[i] = sum;
    }
}