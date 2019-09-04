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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int** dither ; 

__attribute__((used)) static void store_slice_c(uint8_t *dst, const uint16_t *src,
                          int dst_stride, int src_stride,
                          int width, int height, int log2_scale)
{
    int y, x;

#define STORE(pos) do {                                                     \
    temp = ((src[x + y * src_stride + pos] << log2_scale) + d[pos]) >> 8;   \
    if (temp & 0x100) temp = ~(temp >> 31);                                 \
    dst[x + y * dst_stride + pos] = temp;                                   \
} while (0)

    for (y = 0; y < height; y++) {
        const uint8_t *d = dither[y&7];
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
    }
}