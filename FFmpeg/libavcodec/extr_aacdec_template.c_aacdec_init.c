#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  subband_scale; int /*<<< orphan*/  vector_pow43; int /*<<< orphan*/  update_ltp; int /*<<< orphan*/  windowing_and_mdct_ltp; int /*<<< orphan*/  apply_tns; int /*<<< orphan*/  apply_ltp; int /*<<< orphan*/  imdct_and_windowing; } ;
typedef  TYPE_1__ AACContext ;

/* Variables and functions */
 scalar_t__ ARCH_MIPS ; 
 int /*<<< orphan*/  apply_ltp ; 
 int /*<<< orphan*/  apply_tns ; 
 int /*<<< orphan*/  ff_aacdec_init_mips (TYPE_1__*) ; 
 int /*<<< orphan*/  imdct_and_windowing ; 
 int /*<<< orphan*/  subband_scale ; 
 int /*<<< orphan*/  update_ltp ; 
 int /*<<< orphan*/  vector_pow43 ; 
 int /*<<< orphan*/  windowing_and_mdct_ltp ; 

__attribute__((used)) static void aacdec_init(AACContext *c)
{
    c->imdct_and_windowing                      = imdct_and_windowing;
    c->apply_ltp                                = apply_ltp;
    c->apply_tns                                = apply_tns;
    c->windowing_and_mdct_ltp                   = windowing_and_mdct_ltp;
    c->update_ltp                               = update_ltp;
#if USE_FIXED
    c->vector_pow43                             = vector_pow43;
    c->subband_scale                            = subband_scale;
#endif

#if !USE_FIXED
    if(ARCH_MIPS)
        ff_aacdec_init_mips(c);
#endif /* !USE_FIXED */
}