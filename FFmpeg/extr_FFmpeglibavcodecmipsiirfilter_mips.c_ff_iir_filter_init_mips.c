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
typedef  int /*<<< orphan*/  FFIIRFilterContext ;

/* Variables and functions */

void ff_iir_filter_init_mips(FFIIRFilterContext *f) {
#if HAVE_INLINE_ASM
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    f->filter_flt = iir_filter_flt_mips;
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_INLINE_ASM */
}