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
 int FF_ARRAY_ELEMS (int*) ; 
 int TB (int) ; 
 int /*<<< orphan*/  fill_elements (int,int,int*,int*) ; 
 int* table ; 

__attribute__((used)) static void fill_lut(uint32_t *lut)
{
    for (int i = 1; i < FF_ARRAY_ELEMS(table); i += 2) {
        uint32_t a = table[i];
        uint32_t b = TB(i>>1);
        uint32_t c, d;

        c = (b << 16) | table[i-1];
        d = 4 * (3 - b);
        if (d <= 0) {
            lut[2 * a] = c;
            lut[2 * a + 1] = 0;
        } else {
            for (int j = 0; j < 1 << d; j++) {
                uint32_t f = 0xFFFFFFFFu;
                c &= 0xFFFFFFu;
                if ((c & 0xFF00u) != 0x8000u)
                    fill_elements(j, d, &c, &f);
                lut[2 * a + 2 * j] = c;
                lut[2 * a + 2 * j + 1] = f;
            }
        }
    }

    for (int i = 0; i < 32; i += 2) {
        lut[i  ] = 0x68000;
        lut[i+1] = 0;
    }
}