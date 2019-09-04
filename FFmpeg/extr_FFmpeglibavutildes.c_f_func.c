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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int** S_boxes_P_shuffle ; 

__attribute__((used)) static uint32_t f_func(uint32_t r, uint64_t k)
{
    int i;
    uint32_t out = 0;
    // rotate to get first part of E-shuffle in the lowest 6 bits
    r = (r << 1) | (r >> 31);
    // apply S-boxes, those compress the data again from 8 * 6 to 8 * 4 bits
    for (i = 7; i >= 0; i--) {
        uint8_t tmp = (r ^ k) & 0x3f;
#if CONFIG_SMALL
        uint8_t v = S_boxes[i][tmp >> 1];
        if (tmp & 1)
            v >>= 4;
        out = (out >> 4) | (v << 28);
#else
        out |= S_boxes_P_shuffle[i][tmp];
#endif
        // get next 6 bits of E-shuffle and round key k into the lowest bits
        r   = (r >> 4) | (r << 28);
        k >>= 6;
    }
#if CONFIG_SMALL
    out = shuffle(out, P_shuffle, sizeof(P_shuffle));
#endif
    return out;
}