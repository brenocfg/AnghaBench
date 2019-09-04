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
typedef  int /*<<< orphan*/  AACContext ;

/* Variables and functions */

void ff_aacdec_init_mips(AACContext *c)
{
#if HAVE_INLINE_ASM
    c->imdct_and_windowing         = imdct_and_windowing_mips;
    c->apply_ltp                   = apply_ltp_mips;
#if HAVE_MIPSFPU
    c->update_ltp                  = update_ltp_mips;
#endif /* HAVE_MIPSFPU */
#endif /* HAVE_INLINE_ASM */
}