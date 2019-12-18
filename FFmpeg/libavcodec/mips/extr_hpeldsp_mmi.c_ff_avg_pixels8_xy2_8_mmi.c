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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 void* AV_RN32 (int /*<<< orphan*/  const*) ; 
 int rnd_avg32 (int,int) ; 

void ff_avg_pixels8_xy2_8_mmi(uint8_t *block, const uint8_t *pixels,
    ptrdiff_t line_size, int h)
{
    /* FIXME HIGH BIT DEPTH */
    int j;

    for (j = 0; j < 2; j++) {
        int i;
        const uint32_t a = AV_RN32(pixels);
        const uint32_t b = AV_RN32(pixels + 1);
        uint32_t l0 = (a & 0x03030303UL) +
                      (b & 0x03030303UL) +
                           0x02020202UL;
        uint32_t h0 = ((a & 0xFCFCFCFCUL) >> 2) +
                      ((b & 0xFCFCFCFCUL) >> 2);
        uint32_t l1, h1;

        pixels += line_size;
        for (i = 0; i < h; i += 2) {
            uint32_t a = AV_RN32(pixels);
            uint32_t b = AV_RN32(pixels + 1);
            l1 = (a & 0x03030303UL) +
                 (b & 0x03030303UL);
            h1 = ((a & 0xFCFCFCFCUL) >> 2) +
                 ((b & 0xFCFCFCFCUL) >> 2);
            *((uint32_t *) block) = rnd_avg32(*((uint32_t *) block), h0 + h1 + (((l0 + l1) >> 2) & 0x0F0F0F0FUL));
            pixels += line_size;
            block  += line_size;
            a  = AV_RN32(pixels);
            b  = AV_RN32(pixels + 1);
            l0 = (a & 0x03030303UL) +
                 (b & 0x03030303UL) +
                      0x02020202UL;
            h0 = ((a & 0xFCFCFCFCUL) >> 2) +
                 ((b & 0xFCFCFCFCUL) >> 2);
            *((uint32_t *) block) = rnd_avg32(*((uint32_t *) block), h0 + h1 + (((l0 + l1) >> 2) & 0x0F0F0F0FUL));
            pixels += line_size;
            block  += line_size;
        }
        pixels += 4 - line_size * (h + 1);
        block  += 4 - line_size * h;
    }
}