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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_bswap16 (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void bswap16UV_c(uint8_t *_dstU, uint8_t *_dstV, const uint8_t *unused0, const uint8_t *_src1,
                        const uint8_t *_src2, int width, uint32_t *unused)
{
    int i;
    const uint16_t *src1 = (const uint16_t *)_src1,
    *src2                = (const uint16_t *)_src2;
    uint16_t *dstU       = (uint16_t *)_dstU, *dstV = (uint16_t *)_dstV;
    for (i = 0; i < width; i++) {
        dstU[i] = av_bswap16(src1[i]);
        dstV[i] = av_bswap16(src2[i]);
    }
}