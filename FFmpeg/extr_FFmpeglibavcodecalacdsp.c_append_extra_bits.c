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

__attribute__((used)) static void append_extra_bits(int32_t *buffer[2], int32_t *extra_bits_buffer[2],
                              int extra_bits, int channels, int nb_samples)
{
    int i, ch;

    for (ch = 0; ch < channels; ch++)
        for (i = 0; i < nb_samples; i++)
            buffer[ch][i] = (buffer[ch][i] << extra_bits) | extra_bits_buffer[ch][i];
}