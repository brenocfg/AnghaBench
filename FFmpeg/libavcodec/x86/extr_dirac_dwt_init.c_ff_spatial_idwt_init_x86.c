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
typedef  enum dwt_type { ____Placeholder_dwt_type } dwt_type ;
struct TYPE_3__ {int /*<<< orphan*/  horizontal_compose; void* vertical_compose; void* vertical_compose_h0; void* vertical_compose_l0; } ;
typedef  TYPE_1__ DWTContext ;

/* Variables and functions */
 int AV_CPU_FLAG_MMX ; 
 int AV_CPU_FLAG_SSE2 ; 
 int AV_CPU_FLAG_SSSE3 ; 
#define  DWT_DIRAC_DD13_7 132 
#define  DWT_DIRAC_DD9_7 131 
#define  DWT_DIRAC_HAAR0 130 
#define  DWT_DIRAC_HAAR1 129 
#define  DWT_DIRAC_LEGALL5_3 128 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  horizontal_compose_dd97i_ssse3 ; 
 int /*<<< orphan*/  horizontal_compose_haar0i_mmx ; 
 int /*<<< orphan*/  horizontal_compose_haar0i_sse2 ; 
 int /*<<< orphan*/  horizontal_compose_haar1i_mmx ; 
 int /*<<< orphan*/  horizontal_compose_haar1i_sse2 ; 
 scalar_t__ vertical_compose53iL0_mmx ; 
 scalar_t__ vertical_compose53iL0_sse2 ; 
 scalar_t__ vertical_compose_dd137iL0_mmx ; 
 scalar_t__ vertical_compose_dd137iL0_sse2 ; 
 scalar_t__ vertical_compose_dd97iH0_mmx ; 
 scalar_t__ vertical_compose_dd97iH0_sse2 ; 
 scalar_t__ vertical_compose_dirac53iH0_mmx ; 
 scalar_t__ vertical_compose_dirac53iH0_sse2 ; 
 scalar_t__ vertical_compose_haar_mmx ; 
 scalar_t__ vertical_compose_haar_sse2 ; 

void ff_spatial_idwt_init_x86(DWTContext *d, enum dwt_type type)
{
#if HAVE_X86ASM
  int mm_flags = av_get_cpu_flags();

#if !ARCH_X86_64
    if (!(mm_flags & AV_CPU_FLAG_MMX))
        return;

    switch (type) {
    case DWT_DIRAC_DD9_7:
        d->vertical_compose_l0 = (void*)vertical_compose53iL0_mmx;
        d->vertical_compose_h0 = (void*)vertical_compose_dd97iH0_mmx;
        break;
    case DWT_DIRAC_LEGALL5_3:
        d->vertical_compose_l0 = (void*)vertical_compose53iL0_mmx;
        d->vertical_compose_h0 = (void*)vertical_compose_dirac53iH0_mmx;
        break;
    case DWT_DIRAC_DD13_7:
        d->vertical_compose_l0 = (void*)vertical_compose_dd137iL0_mmx;
        d->vertical_compose_h0 = (void*)vertical_compose_dd97iH0_mmx;
        break;
    case DWT_DIRAC_HAAR0:
        d->vertical_compose   = (void*)vertical_compose_haar_mmx;
        d->horizontal_compose = horizontal_compose_haar0i_mmx;
        break;
    case DWT_DIRAC_HAAR1:
        d->vertical_compose   = (void*)vertical_compose_haar_mmx;
        d->horizontal_compose = horizontal_compose_haar1i_mmx;
        break;
    }
#endif

    if (!(mm_flags & AV_CPU_FLAG_SSE2))
        return;

    switch (type) {
    case DWT_DIRAC_DD9_7:
        d->vertical_compose_l0 = (void*)vertical_compose53iL0_sse2;
        d->vertical_compose_h0 = (void*)vertical_compose_dd97iH0_sse2;
        break;
    case DWT_DIRAC_LEGALL5_3:
        d->vertical_compose_l0 = (void*)vertical_compose53iL0_sse2;
        d->vertical_compose_h0 = (void*)vertical_compose_dirac53iH0_sse2;
        break;
    case DWT_DIRAC_DD13_7:
        d->vertical_compose_l0 = (void*)vertical_compose_dd137iL0_sse2;
        d->vertical_compose_h0 = (void*)vertical_compose_dd97iH0_sse2;
        break;
    case DWT_DIRAC_HAAR0:
        d->vertical_compose   = (void*)vertical_compose_haar_sse2;
        d->horizontal_compose = horizontal_compose_haar0i_sse2;
        break;
    case DWT_DIRAC_HAAR1:
        d->vertical_compose   = (void*)vertical_compose_haar_sse2;
        d->horizontal_compose = horizontal_compose_haar1i_sse2;
        break;
    }

    if (!(mm_flags & AV_CPU_FLAG_SSSE3))
        return;

    switch (type) {
    case DWT_DIRAC_DD9_7:
        d->horizontal_compose = horizontal_compose_dd97i_ssse3;
        break;
    }
#endif // HAVE_X86ASM
}