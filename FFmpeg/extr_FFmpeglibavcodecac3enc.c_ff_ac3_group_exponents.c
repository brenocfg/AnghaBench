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
typedef  int uint8_t ;
struct TYPE_5__ {size_t* end_freq; int** grouped_exp; int /*<<< orphan*/ * exp; int /*<<< orphan*/  cpl_in_use; } ;
struct TYPE_4__ {int num_blocks; int channels; int** exp_strategy; size_t* start_freq; TYPE_2__* blocks; } ;
typedef  TYPE_1__ AC3EncodeContext ;
typedef  TYPE_2__ AC3Block ;

/* Variables and functions */
 int CPL_CH ; 
 int EXP_D45 ; 
 int EXP_REUSE ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int*** exponent_group_tab ; 

void ff_ac3_group_exponents(AC3EncodeContext *s)
{
    int blk, ch, i, cpl;
    int group_size, nb_groups;
    uint8_t *p;
    int delta0, delta1, delta2;
    int exp0, exp1;

    for (blk = 0; blk < s->num_blocks; blk++) {
        AC3Block *block = &s->blocks[blk];
        for (ch = !block->cpl_in_use; ch <= s->channels; ch++) {
            int exp_strategy = s->exp_strategy[ch][blk];
            if (exp_strategy == EXP_REUSE)
                continue;
            cpl = (ch == CPL_CH);
            group_size = exp_strategy + (exp_strategy == EXP_D45);
            nb_groups = exponent_group_tab[cpl][exp_strategy-1][block->end_freq[ch]-s->start_freq[ch]];
            p = block->exp[ch] + s->start_freq[ch] - cpl;

            /* DC exponent */
            exp1 = *p++;
            block->grouped_exp[ch][0] = exp1;

            /* remaining exponents are delta encoded */
            for (i = 1; i <= nb_groups; i++) {
                /* merge three delta in one code */
                exp0   = exp1;
                exp1   = p[0];
                p     += group_size;
                delta0 = exp1 - exp0 + 2;
                av_assert2(delta0 >= 0 && delta0 <= 4);

                exp0   = exp1;
                exp1   = p[0];
                p     += group_size;
                delta1 = exp1 - exp0 + 2;
                av_assert2(delta1 >= 0 && delta1 <= 4);

                exp0   = exp1;
                exp1   = p[0];
                p     += group_size;
                delta2 = exp1 - exp0 + 2;
                av_assert2(delta2 >= 0 && delta2 <= 4);

                block->grouped_exp[ch][i] = ((delta0 * 5 + delta1) * 5) + delta2;
            }
        }
    }
}