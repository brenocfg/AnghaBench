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
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static int vp6_block_variance(uint8_t *src, ptrdiff_t stride)
{
    int sum = 0, square_sum = 0;
    int y, x;

    for (y=0; y<8; y+=2) {
        for (x=0; x<8; x+=2) {
            sum += src[x];
            square_sum += src[x]*src[x];
        }
        src += 2*stride;
    }
    return (16*square_sum - sum*sum) >> 8;
}