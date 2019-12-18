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
typedef  int uint16_t ;

/* Variables and functions */

void ff_fft_lut_init(uint16_t *table, int off, int size, int *index)
{
    if (size < 16) {
        table[*index] = off >> 2;
        (*index)++;
    }
    else {
        ff_fft_lut_init(table, off, size>>1, index);
        ff_fft_lut_init(table, off+(size>>1), size>>2, index);
        ff_fft_lut_init(table, off+3*(size>>2), size>>2, index);
    }
}