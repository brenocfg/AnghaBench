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
typedef  int uint16_t ;

/* Variables and functions */
 int av_bswap16 (int const) ; 

__attribute__((used)) static void gbr16ptopacked16(const uint16_t *src[], int srcStride[],
                             uint8_t *dst, int dstStride, int srcSliceH,
                             int alpha, int swap, int bpp, int width)
{
    int x, h, i;
    int src_alpha = src[3] != NULL;
    int scale_high = 16 - bpp, scale_low = (bpp - 8) * 2;
    for (h = 0; h < srcSliceH; h++) {
        uint16_t *dest = (uint16_t *)(dst + dstStride * h);
        uint16_t component;

        switch(swap) {
        case 3:
            if (alpha && !src_alpha) {
                for (x = 0; x < width; x++) {
                    component = av_bswap16(src[0][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[1][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[2][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    *dest++ = 0xffff;
                }
            } else if (alpha && src_alpha) {
                for (x = 0; x < width; x++) {
                    component = av_bswap16(src[0][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[1][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[2][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[3][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                }
            } else {
                for (x = 0; x < width; x++) {
                    component = av_bswap16(src[0][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[1][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                    component = av_bswap16(src[2][x]);
                    *dest++ = av_bswap16(component << scale_high | component >> scale_low);
                }
            }
            break;
        case 2:
            if (alpha && !src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x] << scale_high | src[0][x] >> scale_low);
                    *dest++ = av_bswap16(src[1][x] << scale_high | src[1][x] >> scale_low);
                    *dest++ = av_bswap16(src[2][x] << scale_high | src[2][x] >> scale_low);
                    *dest++ = 0xffff;
                }
            } else if (alpha && src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x] << scale_high | src[0][x] >> scale_low);
                    *dest++ = av_bswap16(src[1][x] << scale_high | src[1][x] >> scale_low);
                    *dest++ = av_bswap16(src[2][x] << scale_high | src[2][x] >> scale_low);
                    *dest++ = av_bswap16(src[3][x] << scale_high | src[3][x] >> scale_low);
                }
            } else {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x] << scale_high | src[0][x] >> scale_low);
                    *dest++ = av_bswap16(src[1][x] << scale_high | src[1][x] >> scale_low);
                    *dest++ = av_bswap16(src[2][x] << scale_high | src[2][x] >> scale_low);
                }
            }
            break;
        case 1:
            if (alpha && !src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x]) << scale_high | av_bswap16(src[0][x]) >> scale_low;
                    *dest++ = av_bswap16(src[1][x]) << scale_high | av_bswap16(src[1][x]) >> scale_low;
                    *dest++ = av_bswap16(src[2][x]) << scale_high | av_bswap16(src[2][x]) >> scale_low;
                    *dest++ = 0xffff;
                }
            } else if (alpha && src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x]) << scale_high | av_bswap16(src[0][x]) >> scale_low;
                    *dest++ = av_bswap16(src[1][x]) << scale_high | av_bswap16(src[1][x]) >> scale_low;
                    *dest++ = av_bswap16(src[2][x]) << scale_high | av_bswap16(src[2][x]) >> scale_low;
                    *dest++ = av_bswap16(src[3][x]) << scale_high | av_bswap16(src[3][x]) >> scale_low;
                }
            } else {
                for (x = 0; x < width; x++) {
                    *dest++ = av_bswap16(src[0][x]) << scale_high | av_bswap16(src[0][x]) >> scale_low;
                    *dest++ = av_bswap16(src[1][x]) << scale_high | av_bswap16(src[1][x]) >> scale_low;
                    *dest++ = av_bswap16(src[2][x]) << scale_high | av_bswap16(src[2][x]) >> scale_low;
                }
            }
            break;
        default:
            if (alpha && !src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = src[0][x] << scale_high | src[0][x] >> scale_low;
                    *dest++ = src[1][x] << scale_high | src[1][x] >> scale_low;
                    *dest++ = src[2][x] << scale_high | src[2][x] >> scale_low;
                    *dest++ = 0xffff;
                }
            } else if (alpha && src_alpha) {
                for (x = 0; x < width; x++) {
                    *dest++ = src[0][x] << scale_high | src[0][x] >> scale_low;
                    *dest++ = src[1][x] << scale_high | src[1][x] >> scale_low;
                    *dest++ = src[2][x] << scale_high | src[2][x] >> scale_low;
                    *dest++ = src[3][x] << scale_high | src[3][x] >> scale_low;
                }
            } else {
                for (x = 0; x < width; x++) {
                    *dest++ = src[0][x] << scale_high | src[0][x] >> scale_low;
                    *dest++ = src[1][x] << scale_high | src[1][x] >> scale_low;
                    *dest++ = src[2][x] << scale_high | src[2][x] >> scale_low;
                }
            }
        }
        for (i = 0; i < 3 + src_alpha; i++)
            src[i] += srcStride[i] >> 1;
    }
}