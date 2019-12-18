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

/* Variables and functions */
#define  EXP_D25 129 
#define  EXP_D45 128 
 int FFMIN (int,int) ; 
 int*** exponent_group_tab ; 

__attribute__((used)) static void encode_exponents_blk_ch(uint8_t *exp, int nb_exps, int exp_strategy,
                                    int cpl)
{
    int nb_groups, i, k;

    nb_groups = exponent_group_tab[cpl][exp_strategy-1][nb_exps] * 3;

    /* for each group, compute the minimum exponent */
    switch(exp_strategy) {
    case EXP_D25:
        for (i = 1, k = 1-cpl; i <= nb_groups; i++) {
            uint8_t exp_min = exp[k];
            if (exp[k+1] < exp_min)
                exp_min = exp[k+1];
            exp[i-cpl] = exp_min;
            k += 2;
        }
        break;
    case EXP_D45:
        for (i = 1, k = 1-cpl; i <= nb_groups; i++) {
            uint8_t exp_min = exp[k];
            if (exp[k+1] < exp_min)
                exp_min = exp[k+1];
            if (exp[k+2] < exp_min)
                exp_min = exp[k+2];
            if (exp[k+3] < exp_min)
                exp_min = exp[k+3];
            exp[i-cpl] = exp_min;
            k += 4;
        }
        break;
    }

    /* constraint for DC exponent */
    if (!cpl && exp[0] > 15)
        exp[0] = 15;

    /* decrease the delta between each groups to within 2 so that they can be
       differentially encoded */
    for (i = 1; i <= nb_groups; i++)
        exp[i] = FFMIN(exp[i], exp[i-1] + 2);
    i--;
    while (--i >= 0)
        exp[i] = FFMIN(exp[i], exp[i+1] + 2);

    if (cpl)
        exp[-1] = exp[0] & ~1;

    /* now we have the exponent values the decoder will see */
    switch (exp_strategy) {
    case EXP_D25:
        for (i = nb_groups, k = (nb_groups * 2)-cpl; i > 0; i--) {
            uint8_t exp1 = exp[i-cpl];
            exp[k--] = exp1;
            exp[k--] = exp1;
        }
        break;
    case EXP_D45:
        for (i = nb_groups, k = (nb_groups * 4)-cpl; i > 0; i--) {
            exp[k] = exp[k-1] = exp[k-2] = exp[k-3] = exp[i-cpl];
            k -= 4;
        }
        break;
    }
}