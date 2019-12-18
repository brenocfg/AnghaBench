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
struct TYPE_3__ {int /*<<< orphan*/  float_to_fixed24; int /*<<< orphan*/  update_bap_counts; int /*<<< orphan*/  bit_alloc_calc_bap; } ;
typedef  TYPE_1__ AC3DSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ac3_bit_alloc_calc_bap_mips ; 
 int /*<<< orphan*/  ac3_update_bap_counts_mips ; 
 int /*<<< orphan*/  float_to_fixed24_mips ; 

void ff_ac3dsp_init_mips(AC3DSPContext *c, int bit_exact) {
#if HAVE_INLINE_ASM
#if HAVE_MIPSDSP
    c->bit_alloc_calc_bap = ac3_bit_alloc_calc_bap_mips;
    c->update_bap_counts  = ac3_update_bap_counts_mips;
#endif
#if HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    c->float_to_fixed24 = float_to_fixed24_mips;
    //c->downmix          = ac3_downmix_mips;
#endif
#endif

#endif
}