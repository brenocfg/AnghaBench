#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int int32_t ;
struct TYPE_5__ {int* end_freq; int num_rematrixing_bands; int** fixed_coef; scalar_t__* rematrixing_flags; scalar_t__ new_rematrixing_strategy; } ;
struct TYPE_4__ {int num_blocks; TYPE_2__* blocks; int /*<<< orphan*/  rematrixing_enabled; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int* ff_ac3_rematrix_band_tab ; 

void ff_ac3_apply_rematrixing(AC3EncodeContext *s)
{
    int nb_coefs;
    int blk, bnd, i;
    int start, end;
    uint8_t *flags = NULL;

    if (!s->rematrixing_enabled)
        return;

    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        if (block->new_rematrixing_strategy)
            flags = block->rematrixing_flags;
        nb_coefs = FFMIN(block->end_freq[1], block->end_freq[2]);
        for (bnd = 0; bnd < block->num_rematrixing_bands; bnd++) {
            if (flags[bnd]) {
                start = ff_ac3_rematrix_band_tab[bnd];
                end   = FFMIN(nb_coefs, ff_ac3_rematrix_band_tab[bnd+1]);
                for (i = start; i < end; i++) {
                    int32_t lt = block->fixed_coef[1][i];
                    int32_t rt = block->fixed_coef[2][i];
                    block->fixed_coef[1][i] = (lt + rt) >> 1;
                    block->fixed_coef[2][i] = (lt - rt) >> 1;
                }
            }
        }
    }
}