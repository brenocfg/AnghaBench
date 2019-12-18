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
struct TYPE_5__ {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * end_freq; int /*<<< orphan*/ * band_psd; int /*<<< orphan*/ * psd; int /*<<< orphan*/ * exp; int /*<<< orphan*/  cpl_in_use; } ;
struct TYPE_4__ {int num_blocks; int channels; scalar_t__** exp_strategy; size_t* fast_gain_code; int lfe_channel; int /*<<< orphan*/ * start_freq; int /*<<< orphan*/  bit_alloc; TYPE_2__* blocks; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 int /*<<< orphan*/  DBA_NONE ; 
 scalar_t__ EXP_REUSE ; 
 int /*<<< orphan*/  ff_ac3_bit_alloc_calc_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_ac3_bit_alloc_calc_psd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_ac3_fast_gain_tab ; 

__attribute__((used)) static void bit_alloc_masking(AC3EncodeContext *s)
{
    int blk, ch;

    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        for (ch = !block->cpl_in_use; ch <= s->channels; ch++) {
            /* We only need psd and mask for calculating bap.
               Since we currently do not calculate bap when exponent
               strategy is EXP_REUSE we do not need to calculate psd or mask. */
            if (s->exp_strategy[ch][blk] != EXP_REUSE) {
                ff_ac3_bit_alloc_calc_psd(block->exp[ch], s->start_freq[ch],
                                          block->end_freq[ch], block->psd[ch],
                                          block->band_psd[ch]);
                ff_ac3_bit_alloc_calc_mask(&s->bit_alloc, block->band_psd[ch],
                                           s->start_freq[ch], block->end_freq[ch],
                                           ff_ac3_fast_gain_tab[s->fast_gain_code[ch]],
                                           ch == s->lfe_channel,
                                           DBA_NONE, 0, NULL, NULL, NULL,
                                           block->mask[ch]);
            }
        }
    }
}