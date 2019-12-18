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
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void copyPlane(const uint8_t *src, int srcStride,
                      int srcSliceY, int srcSliceH, int width,
                      uint8_t *dst, int dstStride)
{
    dst += dstStride * srcSliceY;
    if (dstStride == srcStride && srcStride > 0) {
        memcpy(dst, src, srcSliceH * dstStride);
    } else {
        int i;
        for (i = 0; i < srcSliceH; i++) {
            memcpy(dst, src, width);
            src += srcStride;
            dst += dstStride;
        }
    }
}