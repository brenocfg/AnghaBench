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
struct TYPE_3__ {int /*<<< orphan*/  update_ltp; int /*<<< orphan*/  apply_ltp; int /*<<< orphan*/  imdct_and_windowing; } ;
typedef  TYPE_1__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  apply_ltp_mips ; 
 int /*<<< orphan*/  imdct_and_windowing_mips ; 
 int /*<<< orphan*/  update_ltp_mips ; 

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