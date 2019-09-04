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
typedef  int /*<<< orphan*/  AACSBRContext ;

/* Variables and functions */

void ff_aacsbr_func_ptr_init_mips(AACSBRContext *c)
{
#if HAVE_INLINE_ASM
    c->sbr_lf_gen            = sbr_lf_gen_mips;
    c->sbr_x_gen             = sbr_x_gen_mips;
#if HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    c->sbr_hf_inverse_filter = sbr_hf_inverse_filter_mips;
    c->sbr_hf_assemble       = sbr_hf_assemble_mips;
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_MIPSFPU */
#endif /* HAVE_INLINE_ASM */
}