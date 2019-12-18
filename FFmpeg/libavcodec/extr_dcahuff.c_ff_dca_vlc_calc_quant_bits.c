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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__*** bitalloc_bits ; 
 size_t* bitalloc_offsets ; 
 size_t* bitalloc_sizes ; 

uint32_t ff_dca_vlc_calc_quant_bits(int *values, uint8_t n, uint8_t sel, uint8_t table)
{
    uint8_t i, id;
    uint32_t sum = 0;
    for (i = 0; i < n; i++) {
        id = values[i] - bitalloc_offsets[table];
        av_assert0(id < bitalloc_sizes[table]);
        sum += bitalloc_bits[table][sel][id];
    }
    return sum;
}