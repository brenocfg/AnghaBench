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
struct TYPE_6__ {int new_rematrixing_strategy; int num_rematrixing_bands; int* end_freq; int* rematrixing_flags; scalar_t__* mdct_coef; scalar_t__ cpl_in_use; } ;
struct TYPE_5__ {scalar_t__ channel_mode; int num_blocks; int* start_freq; int /*<<< orphan*/  rematrixing_enabled; TYPE_2__* blocks; } ;
typedef  int CoefSumType ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 scalar_t__ AC3_CHMODE_STEREO ; 
 size_t CPL_CH ; 
 scalar_t__ FFMIN (int,int) ; 
 int* ff_ac3_rematrix_band_tab ; 
 int /*<<< orphan*/  sum_square_butterfly (TYPE_1__*,int*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void compute_rematrixing_strategy(AC3EncodeContext *s)
{
    int nb_coefs;
    int blk, bnd;
    AC3Block *block, *block0 = NULL;

    if (s->channel_mode != AC3_CHMODE_STEREO)
        return;

    for (blk = 0; blk < s->num_blocks; blk++) {
        block = &s->blocks[blk];
        block->new_rematrixing_strategy = !blk;

        block->num_rematrixing_bands = 4;
        if (block->cpl_in_use) {
            block->num_rematrixing_bands -= (s->start_freq[CPL_CH] <= 61);
            block->num_rematrixing_bands -= (s->start_freq[CPL_CH] == 37);
            if (blk && block->num_rematrixing_bands != block0->num_rematrixing_bands)
                block->new_rematrixing_strategy = 1;
        }
        nb_coefs = FFMIN(block->end_freq[1], block->end_freq[2]);

        if (!s->rematrixing_enabled) {
            block0 = block;
            continue;
        }

        for (bnd = 0; bnd < block->num_rematrixing_bands; bnd++) {
            /* calculate sum of squared coeffs for one band in one block */
            int start = ff_ac3_rematrix_band_tab[bnd];
            int end   = FFMIN(nb_coefs, ff_ac3_rematrix_band_tab[bnd+1]);
            CoefSumType sum[4];
            sum_square_butterfly(s, sum, block->mdct_coef[1] + start,
                                 block->mdct_coef[2] + start, end - start);

            /* compare sums to determine if rematrixing will be used for this band */
            if (FFMIN(sum[2], sum[3]) < FFMIN(sum[0], sum[1]))
                block->rematrixing_flags[bnd] = 1;
            else
                block->rematrixing_flags[bnd] = 0;

            /* determine if new rematrixing flags will be sent */
            if (blk &&
                block->rematrixing_flags[bnd] != block0->rematrixing_flags[bnd]) {
                block->new_rematrixing_strategy = 1;
            }
        }
        block0 = block;
    }
}