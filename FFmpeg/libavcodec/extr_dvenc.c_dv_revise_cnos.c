#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int bpm; int* block_sizes; } ;
struct TYPE_5__ {int cno; } ;
typedef  TYPE_1__ EncBlockInfo ;
typedef  TYPE_2__ AVDVProfile ;

/* Variables and functions */

__attribute__((used)) static inline void dv_revise_cnos(uint8_t *dif, EncBlockInfo *blk, const AVDVProfile *profile)
{
    uint8_t *data;
    int mb_index, i;

    for (mb_index = 0; mb_index < 5; mb_index++) {
        data = dif + mb_index*80 + 4;
        for (i = 0; i < profile->bpm; i++) {
            /* zero out the class number */
            data[1] &= 0xCF;
            /* add the new one */
            data[1] |= blk[profile->bpm*mb_index+i].cno << 4;

            data += profile->block_sizes[i] >> 3;
        }
    }
}