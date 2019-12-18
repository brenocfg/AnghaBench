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
struct TYPE_3__ {int /*<<< orphan*/  add_gradient_pred; int /*<<< orphan*/  add_left_pred; int /*<<< orphan*/  add_bytes; int /*<<< orphan*/  add_left_pred_int16; int /*<<< orphan*/  add_median_pred; } ;
typedef  TYPE_1__ LLVidDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86_32 ; 
 int AV_CPU_FLAG_3DNOW ; 
 int AV_CPU_FLAG_CMOV ; 
 scalar_t__ EXTERNAL_AVX2_FAST (int) ; 
 scalar_t__ EXTERNAL_MMX (int) ; 
 scalar_t__ EXTERNAL_MMXEXT (int) ; 
 scalar_t__ EXTERNAL_SSE2 (int) ; 
 scalar_t__ EXTERNAL_SSSE3 (int) ; 
 scalar_t__ EXTERNAL_SSSE3_FAST (int) ; 
 int /*<<< orphan*/  add_median_pred_cmov ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  ff_add_bytes_avx2 ; 
 int /*<<< orphan*/  ff_add_bytes_mmx ; 
 int /*<<< orphan*/  ff_add_bytes_sse2 ; 
 int /*<<< orphan*/  ff_add_gradient_pred_avx2 ; 
 int /*<<< orphan*/  ff_add_gradient_pred_ssse3 ; 
 int /*<<< orphan*/  ff_add_left_pred_int16_ssse3 ; 
 int /*<<< orphan*/  ff_add_left_pred_int16_unaligned_ssse3 ; 
 int /*<<< orphan*/  ff_add_left_pred_ssse3 ; 
 int /*<<< orphan*/  ff_add_left_pred_unaligned_avx2 ; 
 int /*<<< orphan*/  ff_add_left_pred_unaligned_ssse3 ; 
 int /*<<< orphan*/  ff_add_median_pred_mmxext ; 
 int /*<<< orphan*/  ff_add_median_pred_sse2 ; 

void ff_llviddsp_init_x86(LLVidDSPContext *c)
{
    int cpu_flags = av_get_cpu_flags();

#if HAVE_INLINE_ASM && HAVE_7REGS && ARCH_X86_32
    if (cpu_flags & AV_CPU_FLAG_CMOV)
        c->add_median_pred = add_median_pred_cmov;
#endif

    if (ARCH_X86_32 && EXTERNAL_MMX(cpu_flags)) {
        c->add_bytes = ff_add_bytes_mmx;
    }

    if (ARCH_X86_32 && EXTERNAL_MMXEXT(cpu_flags)) {
        /* slower than cmov version on AMD */
        if (!(cpu_flags & AV_CPU_FLAG_3DNOW))
            c->add_median_pred = ff_add_median_pred_mmxext;
    }

    if (EXTERNAL_SSE2(cpu_flags)) {
        c->add_bytes       = ff_add_bytes_sse2;
        c->add_median_pred = ff_add_median_pred_sse2;
    }

    if (EXTERNAL_SSSE3(cpu_flags)) {
        c->add_left_pred = ff_add_left_pred_ssse3;
        c->add_left_pred_int16 = ff_add_left_pred_int16_ssse3;
        c->add_gradient_pred   = ff_add_gradient_pred_ssse3;
    }

    if (EXTERNAL_SSSE3_FAST(cpu_flags)) {
        c->add_left_pred = ff_add_left_pred_unaligned_ssse3;
        c->add_left_pred_int16 = ff_add_left_pred_int16_unaligned_ssse3;
    }

    if (EXTERNAL_AVX2_FAST(cpu_flags)) {
        c->add_bytes       = ff_add_bytes_avx2;
        c->add_left_pred   = ff_add_left_pred_unaligned_avx2;
        c->add_gradient_pred = ff_add_gradient_pred_avx2;
    }
}