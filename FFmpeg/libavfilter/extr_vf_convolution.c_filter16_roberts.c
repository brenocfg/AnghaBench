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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int AV_RN16A (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_clip (float,int /*<<< orphan*/ ,int) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void filter16_roberts(uint8_t *dstp, int width,
                             float scale, float delta, const int *const matrix,
                             const uint8_t *c[], int peak, int radius,
                             int dstride, int stride)
{
    uint16_t *dst = (uint16_t *)dstp;
    int x;

    for (x = 0; x < width; x++) {
        float suma = AV_RN16A(&c[0][2 * x]) *  1 + AV_RN16A(&c[1][2 * x]) * -1;
        float sumb = AV_RN16A(&c[4][2 * x]) *  1 + AV_RN16A(&c[3][2 * x]) * -1;

        dst[x] = av_clip(sqrtf(suma*suma + sumb*sumb) * scale + delta, 0, peak);
    }
}