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
 int /*<<< orphan*/  STORE2 (int) ; 
 int /*<<< orphan*/ ** dither ; 

__attribute__((used)) static void store_slice2_c(uint8_t *dst, int16_t *src,
                           ptrdiff_t dst_stride, ptrdiff_t src_stride,
                           ptrdiff_t width, ptrdiff_t height, ptrdiff_t log2_scale)
{
    int y, x;
#define STORE2(pos)                                                                                       \
    temp = (src[x + pos] + src[x + pos + 16 * src_stride] + (d[pos] >> log2_scale)) >> (6 - log2_scale);  \
    src[x + pos + 16 * src_stride] = 0;                                                                   \
    if (temp & 0x100) temp = ~(temp >> 31);                                                               \
    dst[x + pos] = temp;

    for (y = 0; y < height; y++) {
        const uint8_t *d = dither[y];
        for (x = 0; x < width; x += 8) {
            int temp;
            STORE2(0);
            STORE2(1);
            STORE2(2);
            STORE2(3);
            STORE2(4);
            STORE2(5);
            STORE2(6);
            STORE2(7);
        }
        src += src_stride;
        dst += dst_stride;
    }
}