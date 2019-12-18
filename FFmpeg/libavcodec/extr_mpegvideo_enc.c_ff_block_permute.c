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
typedef  scalar_t__ int16_t ;

/* Variables and functions */

void ff_block_permute(int16_t *block, uint8_t *permutation,
                      const uint8_t *scantable, int last)
{
    int i;
    int16_t temp[64];

    if (last <= 0)
        return;
    //FIXME it is ok but not clean and might fail for some permutations
    // if (permutation[1] == 1)
    // return;

    for (i = 0; i <= last; i++) {
        const int j = scantable[i];
        temp[j] = block[j];
        block[j] = 0;
    }

    for (i = 0; i <= last; i++) {
        const int j = scantable[i];
        const int perm_j = permutation[j];
        block[perm_j] = temp[j];
    }
}