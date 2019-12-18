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

/* Variables and functions */
 int area2 ; 
 int area4 ; 

__attribute__((used)) static void spatial_compensation_5(uint8_t *src, uint8_t *dst, ptrdiff_t stride)
{
    int x, y;

    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            if (2 * x - y < 0)
                dst[x] = src[area2 + 9 + 2 * x - y];
            else
                dst[x] = src[area4 + x - ((y + 1) >> 1)];
        }
        dst += stride;
    }
}