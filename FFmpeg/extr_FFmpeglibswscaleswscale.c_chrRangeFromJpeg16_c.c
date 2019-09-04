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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */

__attribute__((used)) static void chrRangeFromJpeg16_c(int16_t *_dstU, int16_t *_dstV, int width)
{
    int i;
    int32_t *dstU = (int32_t *) _dstU;
    int32_t *dstV = (int32_t *) _dstV;
    for (i = 0; i < width; i++) {
        dstU[i] = (dstU[i] * 1799 + (4081085 << 4)) >> 11; // 1469
        dstV[i] = (dstV[i] * 1799 + (4081085 << 4)) >> 11; // 1469
    }
}