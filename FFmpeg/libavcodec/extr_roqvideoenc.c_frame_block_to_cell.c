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

/* Variables and functions */

__attribute__((used)) static inline void frame_block_to_cell(uint8_t *block, uint8_t * const *data,
                                       int top, int left, const int *stride)
{
    int i, j, u=0, v=0;

    for (i=0; i<2; i++)
        for (j=0; j<2; j++) {
            int x = (top+i)*stride[0] + left + j;
            *block++ = data[0][x];
            x = (top+i)*stride[1] + left + j;
            u       += data[1][x];
            v       += data[2][x];
        }

    *block++ = (u+2)/4;
    *block++ = (v+2)/4;
}