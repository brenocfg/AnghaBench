#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dct32_float; int /*<<< orphan*/  imdct36_blocks_float; int /*<<< orphan*/  apply_window_float; } ;
typedef  TYPE_1__ MPADSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_dct32_mips_float ; 
 int /*<<< orphan*/  ff_imdct36_blocks_mips_float ; 
 int /*<<< orphan*/  ff_mpadsp_apply_window_mips_float ; 

void ff_mpadsp_init_mipsfpu(MPADSPContext *s)
{
#if HAVE_INLINE_ASM && HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    s->apply_window_float   = ff_mpadsp_apply_window_mips_float;
    s->imdct36_blocks_float = ff_imdct36_blocks_mips_float;
    s->dct32_float          = ff_dct32_mips_float;
#endif
#endif
}