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
struct TYPE_3__ {int /*<<< orphan*/  vector_fmul_reverse; int /*<<< orphan*/  butterflies_float; int /*<<< orphan*/  vector_fmul_window; int /*<<< orphan*/  vector_fmul_scalar; int /*<<< orphan*/  vector_fmul; } ;
typedef  TYPE_1__ AVFloatDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  butterflies_float_mips ; 
 int /*<<< orphan*/  vector_fmul_mips ; 
 int /*<<< orphan*/  vector_fmul_reverse_mips ; 
 int /*<<< orphan*/  vector_fmul_scalar_mips ; 
 int /*<<< orphan*/  vector_fmul_window_mips ; 

void ff_float_dsp_init_mips(AVFloatDSPContext *fdsp) {
#if HAVE_INLINE_ASM && HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    fdsp->vector_fmul = vector_fmul_mips;
    fdsp->vector_fmul_scalar  = vector_fmul_scalar_mips;
    fdsp->vector_fmul_window = vector_fmul_window_mips;
    fdsp->butterflies_float = butterflies_float_mips;
    fdsp->vector_fmul_reverse = vector_fmul_reverse_mips;
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_INLINE_ASM && HAVE_MIPSFPU */
}