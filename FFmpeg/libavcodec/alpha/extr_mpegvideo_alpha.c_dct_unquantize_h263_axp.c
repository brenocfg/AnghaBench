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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int WORD_VEC (int) ; 
 int cmpbge (int,int) ; 
 int ldq (int /*<<< orphan*/ *) ; 
 int maxsw4 (int,int) ; 
 int minsw4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stq (int,int /*<<< orphan*/ *) ; 
 int zap (int,int) ; 

__attribute__((used)) static void dct_unquantize_h263_axp(int16_t *block, int n_coeffs,
                                    uint64_t qscale, uint64_t qadd)
{
    uint64_t qmul = qscale << 1;
    uint64_t correction = WORD_VEC(qmul * 255 >> 8);
    int i;

    qadd = WORD_VEC(qadd);

    for(i = 0; i <= n_coeffs; block += 4, i += 4) {
        uint64_t levels, negmask, zeros, add, sub;

        levels = ldq(block);
        if (levels == 0)
            continue;

#ifdef __alpha_max__
        /* I don't think the speed difference justifies runtime
           detection.  */
        negmask = maxsw4(levels, -1); /* negative -> ffff (-1) */
        negmask = minsw4(negmask, 0); /* positive -> 0000 (0) */
#else
        negmask = cmpbge(WORD_VEC(0x7fff), levels);
        negmask &= (negmask >> 1) | (1 << 7);
        negmask = zap(-1, negmask);
#endif

        zeros = cmpbge(0, levels);
        zeros &= zeros >> 1;
        /* zeros |= zeros << 1 is not needed since qadd <= 255, so
           zapping the lower byte suffices.  */

        levels *= qmul;
        levels -= correction & (negmask << 16);

        add = qadd & ~negmask;
        sub = qadd &  negmask;
        /* Set qadd to 0 for levels == 0.  */
        add = zap(add, zeros);
        levels += add;
        levels -= sub;

        stq(levels, block);
    }
}