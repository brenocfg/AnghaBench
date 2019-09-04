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
typedef  int int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int av_log2 (int) ; 
 int clip23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  norm__ (int const,int) ; 

__attribute__((used)) static inline void ff_dca_core_dequantize(int32_t *output, const int32_t *input,
                                          int32_t step_size, int32_t scale, int residual, int len)
{
    // Account for quantizer step size
    int64_t step_scale = (int64_t)step_size * scale;
    int n, shift = 0;

    // Limit scale factor resolution to 22 bits
    if (step_scale > (1 << 23)) {
        shift = av_log2(step_scale >> 23) + 1;
        step_scale >>= shift;
    }

    // Scale the samples
    if (residual) {
        for (n = 0; n < len; n++)
            output[n] += clip23(norm__(input[n] * step_scale, 22 - shift));
    } else {
        for (n = 0; n < len; n++)
            output[n]  = clip23(norm__(input[n] * step_scale, 22 - shift));
    }
}