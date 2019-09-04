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
struct TYPE_5__ {int* end_freq; int /*<<< orphan*/  cpl_in_use; } ;
struct TYPE_4__ {int num_blocks; int channels; int** exp_strategy; int* start_freq; TYPE_2__* blocks; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 int CPL_CH ; 
 int EXP_REUSE ; 
 int*** exponent_group_tab ; 

__attribute__((used)) static int count_exponent_bits(AC3EncodeContext *s)
{
    int blk, ch;
    int nb_groups, bit_count;

    bit_count = 0;
    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        for (ch = !block->cpl_in_use; ch <= s->channels; ch++) {
            int exp_strategy = s->exp_strategy[ch][blk];
            int cpl          = (ch == CPL_CH);
            int nb_coefs     = block->end_freq[ch] - s->start_freq[ch];

            if (exp_strategy == EXP_REUSE)
                continue;

            nb_groups = exponent_group_tab[cpl][exp_strategy-1][nb_coefs];
            bit_count += 4 + (nb_groups * 7);
        }
    }

    return bit_count;
}