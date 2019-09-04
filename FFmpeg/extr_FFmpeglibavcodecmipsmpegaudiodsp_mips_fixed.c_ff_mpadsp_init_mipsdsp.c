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
typedef  int /*<<< orphan*/  MPADSPContext ;

/* Variables and functions */

void ff_mpadsp_init_mipsdsp(MPADSPContext *s)
{
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    s->apply_window_fixed   = ff_mpadsp_apply_window_mips_fixed;
    s->imdct36_blocks_fixed = ff_imdct36_blocks_mips_fixed;
#endif
#endif
}