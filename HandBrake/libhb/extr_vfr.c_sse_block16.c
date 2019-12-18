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
typedef  size_t uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline unsigned sse_block16( unsigned *gamma_lut, uint8_t *a, uint8_t *b, int stride )
{
    int x, y;
    unsigned sum = 0;
    int diff;

    for( y = 0; y < 16; y++ )
    {
        for( x = 0; x < 16; x++ )
        {
            diff =  gamma_lut[a[x]] - gamma_lut[b[x]];
            sum += diff * diff;
        }
        a += stride;
        b += stride;
    }
    return sum;
}