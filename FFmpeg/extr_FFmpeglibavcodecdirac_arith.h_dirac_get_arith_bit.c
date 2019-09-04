#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* contexts; unsigned int low; int range; } ;
typedef  TYPE_1__ DiracArith ;

/* Variables and functions */
 scalar_t__** ff_dirac_prob_branchless ; 
 int /*<<< orphan*/  refill (TYPE_1__*) ; 
 int /*<<< orphan*/  renorm (TYPE_1__*) ; 

__attribute__((used)) static inline int dirac_get_arith_bit(DiracArith *c, int ctx)
{
    int prob_zero = c->contexts[ctx];
    int range_times_prob, bit;
    unsigned low = c->low;
    int    range = c->range;

    range_times_prob = (c->range * prob_zero) >> 16;

#if ARCH_X86 && HAVE_FAST_CMOV && HAVE_INLINE_ASM && HAVE_6REGS
    low   -= range_times_prob << 16;
    range -= range_times_prob;
    bit = 0;
    __asm__(
        "cmpl   %5, %4 \n\t"
        "setae  %b0    \n\t"
        "cmovb  %3, %2 \n\t"
        "cmovb  %5, %1 \n\t"
        : "+q"(bit), "+r"(range), "+r"(low)
        : "r"(c->low), "r"(c->low>>16),
          "r"(range_times_prob)
    );
#else
    bit = (low >> 16) >= range_times_prob;
    if (bit) {
        low   -= range_times_prob << 16;
        range -= range_times_prob;
    } else {
        range  = range_times_prob;
    }
#endif

    c->contexts[ctx] += ff_dirac_prob_branchless[prob_zero>>8][bit];
    c->low   = low;
    c->range = range;

    renorm(c);
    refill(c);
    return bit;
}