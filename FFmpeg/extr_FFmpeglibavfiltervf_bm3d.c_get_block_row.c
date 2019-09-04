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
typedef  float uint8_t ;

/* Variables and functions */

__attribute__((used)) static void get_block_row(const uint8_t *srcp, int src_linesize,
                          int y, int x, int block_size, float *dst)
{
    const uint8_t *src = srcp + y * src_linesize + x;
    int j;

    for (j = 0; j < block_size; j++) {
        dst[j] = src[j];
    }
}