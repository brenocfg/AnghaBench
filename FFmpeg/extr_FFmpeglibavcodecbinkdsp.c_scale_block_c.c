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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void scale_block_c(const uint8_t src[64]/*align 8*/, uint8_t *dst/*align 8*/, int linesize)
{
    int i, j;
    uint16_t *dst1 = (uint16_t *) dst;
    uint16_t *dst2 = (uint16_t *)(dst + linesize);

    for (j = 0; j < 8; j++) {
        for (i = 0; i < 8; i++) {
            dst1[i] = dst2[i] = src[i] * 0x0101;
        }
        src  += 8;
        dst1 += linesize;
        dst2 += linesize;
    }
}