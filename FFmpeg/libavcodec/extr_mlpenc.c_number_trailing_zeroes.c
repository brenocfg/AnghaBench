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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static int number_trailing_zeroes(int32_t sample)
{
    int bits;

    for (bits = 0; bits < 24 && !(sample & (1<<bits)); bits++);

    /* All samples are 0. TODO Return previous quant_step_size to avoid
     * writing a new header. */
    if (bits == 24)
        return 0;

    return bits;
}