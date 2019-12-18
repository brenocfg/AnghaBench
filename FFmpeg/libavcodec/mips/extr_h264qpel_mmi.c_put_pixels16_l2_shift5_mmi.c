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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_pixels8_l2_shift5_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void put_pixels16_l2_shift5_mmi(uint8_t *dst, int16_t *src16,
        const uint8_t *src8, ptrdiff_t dstStride, ptrdiff_t src8Stride, int h)
{
    put_pixels8_l2_shift5_mmi(dst, src16, src8, dstStride, src8Stride, h);
    put_pixels8_l2_shift5_mmi(dst + 8, src16 + 8, src8 + 8, dstStride,
            src8Stride, h);
}