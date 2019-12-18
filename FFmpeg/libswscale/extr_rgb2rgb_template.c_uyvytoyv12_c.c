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

/* Variables and functions */

__attribute__((used)) static inline void uyvytoyv12_c(const uint8_t *src, uint8_t *ydst,
                                uint8_t *udst, uint8_t *vdst,
                                int width, int height, int lumStride,
                                int chromStride, int srcStride)
{
    int y;
    const int chromWidth = width >> 1;

    for (y = 0; y < height; y += 2) {
        int i;
        for (i = 0; i < chromWidth; i++) {
            udst[i]         = src[4 * i + 0];
            ydst[2 * i + 0] = src[4 * i + 1];
            vdst[i]         = src[4 * i + 2];
            ydst[2 * i + 1] = src[4 * i + 3];
        }
        ydst += lumStride;
        src  += srcStride;

        for (i = 0; i < chromWidth; i++) {
            ydst[2 * i + 0] = src[4 * i + 1];
            ydst[2 * i + 1] = src[4 * i + 3];
        }
        udst += chromStride;
        vdst += chromStride;
        ydst += lumStride;
        src  += srcStride;
    }
}