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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 scalar_t__ av_clip_uint8 (scalar_t__) ; 

__attribute__((used)) static void rv34_idct_dc_add_c(uint8_t *dst, ptrdiff_t stride, int dc)
{
    int i, j;

    dc = (13*13*dc + 0x200) >> 10;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
            dst[j] = av_clip_uint8( dst[j] + dc );

        dst += stride;
    }
}