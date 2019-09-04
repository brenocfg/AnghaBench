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
typedef  int /*<<< orphan*/  CELPMContext ;

/* Variables and functions */

void ff_celp_math_init_mips(CELPMContext *c)
{
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    c->dot_productf = ff_dot_productf_mips;
#endif
#endif
}