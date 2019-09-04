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
typedef  size_t uint16_t ;

/* Variables and functions */
 int* ff_reverse ; 

__attribute__((used)) static uint16_t inv_bits(uint16_t val, int nbits)
{
    uint16_t res;

    if (nbits <= 8) {
        res = ff_reverse[val] >> (8 - nbits);
    } else
        res = ((ff_reverse[val & 0xFF] << 8) +
               (ff_reverse[val >> 8])) >> (16 - nbits);

    return res;
}