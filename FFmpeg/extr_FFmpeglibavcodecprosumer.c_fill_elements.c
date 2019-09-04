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
typedef  int uint32_t ;

/* Variables and functions */
 int TB (int) ; 
 int* table ; 

__attribute__((used)) static void fill_elements(uint32_t idx, uint32_t shift, uint32_t *e0, uint32_t *e1)
{
    uint32_t b, h = idx << (32 - shift);

    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 43; i++) {
            b = 4 * TB(i);
            if (shift >= b && ((h & (0xFFF00000u << (12 - b))) >> 20) == table[2 * i + 1]) {
                if (table[2 * i] >> 8 == 0x80u) {
                    return;
                } else {
                    *e0 = (*e0 & 0xFFFFFFu) | (((12 + b - shift)  | (0x40u<<j)) << 22);
                    if (j == 0) {
                        *e1 = table[2 * i];
                        shift -= b;
                        h <<= b;
                    } else {
                        *e1 |= (unsigned)table[2 * i] << 16;
                    }
                    break;
                }
            }
        }
    }
}