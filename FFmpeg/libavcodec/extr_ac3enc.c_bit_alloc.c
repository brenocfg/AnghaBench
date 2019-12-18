#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * end_freq; int /*<<< orphan*/ * psd; int /*<<< orphan*/ * mask; int /*<<< orphan*/  cpl_in_use; } ;
struct TYPE_9__ {int /*<<< orphan*/  floor; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* bit_alloc_calc_bap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int num_blocks; int channels; scalar_t__** exp_strategy; int /*<<< orphan*/ ** ref_bap; TYPE_2__ bit_alloc; int /*<<< orphan*/ * start_freq; TYPE_1__ ac3dsp; TYPE_4__* blocks; } ;
typedef  TYPE_3__ AC3EncodeContext ;
typedef  TYPE_4__ AC3Block ;

/* Variables and functions */
 scalar_t__ EXP_REUSE ; 
 int count_mantissa_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_ac3_bap_tab ; 
 int /*<<< orphan*/  reset_block_bap (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bit_alloc(AC3EncodeContext *s, int snr_offset)
{
    int blk, ch;

    snr_offset = (snr_offset - 240) * 4;

    reset_block_bap(s);
    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];

        for (ch = !block->cpl_in_use; ch <= s->channels; ch++) {
            /* Currently the only bit allocation parameters which vary across
               blocks within a frame are the exponent values.  We can take
               advantage of that by reusing the bit allocation pointers
               whenever we reuse exponents. */
            if (s->exp_strategy[ch][blk] != EXP_REUSE) {
                s->ac3dsp.bit_alloc_calc_bap(block->mask[ch], block->psd[ch],
                                             s->start_freq[ch], block->end_freq[ch],
                                             snr_offset, s->bit_alloc.floor,
                                             ff_ac3_bap_tab, s->ref_bap[ch][blk]);
            }
        }
    }
    return count_mantissa_bits(s);
}