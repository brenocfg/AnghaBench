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
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  extract_even2_c (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  extract_even_c (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void uyvytoyuv422_c(uint8_t *ydst, uint8_t *udst, uint8_t *vdst,
                           const uint8_t *src, int width, int height,
                           int lumStride, int chromStride, int srcStride)
{
    int y;
    const int chromWidth = AV_CEIL_RSHIFT(width, 1);

    for (y = 0; y < height; y++) {
        extract_even_c(src + 1, ydst, width);
        extract_even2_c(src, udst, vdst, chromWidth);

        src  += srcStride;
        ydst += lumStride;
        udst += chromStride;
        vdst += chromStride;
    }
}