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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  STORE (int) ; 
 int /*<<< orphan*/ ** dither ; 

__attribute__((used)) static void store_slice_c(uint8_t *dst, int16_t *src,
                          ptrdiff_t dst_stride, ptrdiff_t src_stride,
                          ptrdiff_t width, ptrdiff_t height, ptrdiff_t log2_scale)
{
    int y, x;
#define STORE(pos)                                                             \
    temp = (src[x + pos] + (d[pos] >> log2_scale)) >> (6 - log2_scale);        \
    src[x + pos] = src[x + pos - 8 * src_stride] = 0;                          \
    if (temp & 0x100) temp = ~(temp >> 31);                                    \
    dst[x + pos] = temp;

    for (y = 0; y < height; y++) {
        const uint8_t *d = dither[y];
        for (x = 0; x < width; x += 8) {
            int temp;
            STORE(0);
            STORE(1);
            STORE(2);
            STORE(3);
            STORE(4);
            STORE(5);
            STORE(6);
            STORE(7);
        }
        src += src_stride;
        dst += dst_stride;
    }
}