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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__ const) ; 

__attribute__((used)) static uint64_t image_sad(const uint16_t *img1, const uint16_t *img2, int w,
                          int h, ptrdiff_t _img1_stride, ptrdiff_t _img2_stride)
{
    ptrdiff_t img1_stride = _img1_stride / sizeof(*img1);
    ptrdiff_t img2_stride = _img2_stride / sizeof(*img2);
    uint64_t sum = 0;
    int i, j;

    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            sum += abs(img1[j] - img2[j]);
        }
        img1 += img1_stride;
        img2 += img2_stride;
    }

    return sum;
}