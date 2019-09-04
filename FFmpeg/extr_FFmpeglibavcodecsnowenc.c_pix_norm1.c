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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__* ff_square_tab ; 

__attribute__((used)) static int pix_norm1(uint8_t * pix, int line_size, int w)
{
    int s, i, j;
    const uint32_t *sq = ff_square_tab + 256;

    s = 0;
    for (i = 0; i < w; i++) {
        for (j = 0; j < w; j ++) {
            s += sq[pix[0]];
            pix ++;
        }
        pix += line_size - w;
    }
    return s;
}