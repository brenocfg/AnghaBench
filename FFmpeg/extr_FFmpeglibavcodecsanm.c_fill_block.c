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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static void fill_block(uint16_t *pdest, uint16_t color, int block_size, ptrdiff_t pitch)
{
    int x, y;

    pitch -= block_size;
    for (y = 0; y < block_size; y++, pdest += pitch)
        for (x = 0; x < block_size; x++)
            *pdest++ = color;
}