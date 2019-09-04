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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int area2 ; 
 int area3 ; 

__attribute__((used)) static void spatial_compensation_7(uint8_t *src, uint8_t *dst, ptrdiff_t stride)
{
    int x, y;

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            if (x - 2 * y > 0)
                dst[x] = (src[area3 - 1 + x - 2 * y] + src[area3 + x - 2 * y] + 1) >> 1;
            else
                dst[x] = src[area2 + 8 - y + (x >> 1)];
        }
        dst += stride;
    }
}