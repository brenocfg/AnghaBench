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
typedef  int /*<<< orphan*/  ACELPFContext ;

/* Variables and functions */

void ff_acelp_filter_init_mips(ACELPFContext *c)
{
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    c->acelp_interpolatef                      = ff_acelp_interpolatef_mips;
    c->acelp_apply_order_2_transfer_function   = ff_acelp_apply_order_2_transfer_function_mips;
#endif
#endif
}