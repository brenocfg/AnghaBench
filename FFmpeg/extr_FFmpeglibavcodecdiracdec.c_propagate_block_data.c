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
typedef  int /*<<< orphan*/  DiracBlock ;

/* Variables and functions */

__attribute__((used)) static void propagate_block_data(DiracBlock *block, int stride, int size)
{
    int x, y;
    DiracBlock *dst = block;

    for (x = 1; x < size; x++)
        dst[x] = *block;

    for (y = 1; y < size; y++) {
        dst += stride;
        for (x = 0; x < size; x++)
            dst[x] = *block;
    }
}