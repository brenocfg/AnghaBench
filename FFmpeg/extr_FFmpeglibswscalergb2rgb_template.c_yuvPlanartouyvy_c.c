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
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static inline void yuvPlanartouyvy_c(const uint8_t *ysrc, const uint8_t *usrc,
                                     const uint8_t *vsrc, uint8_t *dst,
                                     int width, int height,
                                     int lumStride, int chromStride,
                                     int dstStride, int vertLumPerChroma)
{
    int y, i;
    const int chromWidth = width >> 1;

    for (y = 0; y < height; y++) {
#if HAVE_FAST_64BIT
        uint64_t *ldst = (uint64_t *)dst;
        const uint8_t *yc = ysrc, *uc = usrc, *vc = vsrc;
        for (i = 0; i < chromWidth; i += 2) {
            uint64_t k = uc[0] + (yc[0] << 8) +
                         (vc[0] << 16) + ((unsigned) yc[1] << 24);
            uint64_t l = uc[1] + (yc[2] << 8) +
                         (vc[1] << 16) + ((unsigned) yc[3] << 24);
            *ldst++ = k + (l << 32);
            yc     += 4;
            uc     += 2;
            vc     += 2;
        }

#else
        int *idst = (int32_t *)dst;
        const uint8_t *yc = ysrc, *uc = usrc, *vc = vsrc;

        for (i = 0; i < chromWidth; i++) {
#if HAVE_BIGENDIAN
            *idst++ = (uc[0] << 24) + (yc[0] << 16) +
                      (vc[0] <<  8) + (yc[1] <<  0);
#else
            *idst++ = uc[0] + (yc[0] << 8) +
                      (vc[0] << 16) + (yc[1] << 24);
#endif
            yc += 2;
            uc++;
            vc++;
        }
#endif
        if ((y & (vertLumPerChroma - 1)) == vertLumPerChroma - 1) {
            usrc += chromStride;
            vsrc += chromStride;
        }
        ysrc += lumStride;
        dst  += dstStride;
    }
}