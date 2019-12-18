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
struct TYPE_3__ {void** put_signed_rect_clamped; int /*<<< orphan*/ * dequant_subband; int /*<<< orphan*/ ** avg_dirac_pixels_tab; int /*<<< orphan*/ ** put_dirac_pixels_tab; int /*<<< orphan*/ * add_dirac_obmc; int /*<<< orphan*/  add_rect_clamped; int /*<<< orphan*/  dirac_hpel_filter; } ;
typedef  TYPE_1__ DiracDSPContext ;

/* Variables and functions */
 scalar_t__ EXTERNAL_MMX (int) ; 
 scalar_t__ EXTERNAL_MMXEXT (int) ; 
 scalar_t__ EXTERNAL_SSE2 (int) ; 
 scalar_t__ EXTERNAL_SSE4 (int) ; 
 int /*<<< orphan*/  PIXFUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_get_cpu_flags () ; 
 int /*<<< orphan*/  avg ; 
 int /*<<< orphan*/  dirac_hpel_filter_mmx ; 
 int /*<<< orphan*/  dirac_hpel_filter_sse2 ; 
 int /*<<< orphan*/  ff_add_dirac_obmc16_mmx ; 
 int /*<<< orphan*/  ff_add_dirac_obmc16_sse2 ; 
 int /*<<< orphan*/  ff_add_dirac_obmc32_mmx ; 
 int /*<<< orphan*/  ff_add_dirac_obmc32_sse2 ; 
 int /*<<< orphan*/  ff_add_dirac_obmc8_mmx ; 
 int /*<<< orphan*/  ff_add_rect_clamped_mmx ; 
 int /*<<< orphan*/  ff_add_rect_clamped_sse2 ; 
 int /*<<< orphan*/  ff_avg_dirac_pixels16_sse2 ; 
 int /*<<< orphan*/  ff_avg_dirac_pixels32_sse2 ; 
 int /*<<< orphan*/  ff_dequant_subband_32_sse4 ; 
 int /*<<< orphan*/  ff_put_dirac_pixels16_sse2 ; 
 int /*<<< orphan*/  ff_put_dirac_pixels32_sse2 ; 
 void* ff_put_signed_rect_clamped_10_sse4 ; 
 scalar_t__ ff_put_signed_rect_clamped_mmx ; 
 scalar_t__ ff_put_signed_rect_clamped_sse2 ; 
 int /*<<< orphan*/  mmx ; 
 int /*<<< orphan*/  mmxext ; 
 int /*<<< orphan*/  put ; 

void ff_diracdsp_init_x86(DiracDSPContext* c)
{
    int mm_flags = av_get_cpu_flags();

    if (EXTERNAL_MMX(mm_flags)) {
        c->add_dirac_obmc[0] = ff_add_dirac_obmc8_mmx;
#if !ARCH_X86_64
        c->add_dirac_obmc[1] = ff_add_dirac_obmc16_mmx;
        c->add_dirac_obmc[2] = ff_add_dirac_obmc32_mmx;
        c->dirac_hpel_filter = dirac_hpel_filter_mmx;
        c->add_rect_clamped = ff_add_rect_clamped_mmx;
        c->put_signed_rect_clamped[0] = (void *)ff_put_signed_rect_clamped_mmx;
#endif
        PIXFUNC(put, 0, mmx);
        PIXFUNC(avg, 0, mmx);
    }

    if (EXTERNAL_MMXEXT(mm_flags)) {
        PIXFUNC(avg, 0, mmxext);
    }

    if (EXTERNAL_SSE2(mm_flags)) {
        c->dirac_hpel_filter = dirac_hpel_filter_sse2;
        c->add_rect_clamped = ff_add_rect_clamped_sse2;
        c->put_signed_rect_clamped[0] = (void *)ff_put_signed_rect_clamped_sse2;

        c->add_dirac_obmc[1] = ff_add_dirac_obmc16_sse2;
        c->add_dirac_obmc[2] = ff_add_dirac_obmc32_sse2;

        c->put_dirac_pixels_tab[1][0] = ff_put_dirac_pixels16_sse2;
        c->avg_dirac_pixels_tab[1][0] = ff_avg_dirac_pixels16_sse2;
        c->put_dirac_pixels_tab[2][0] = ff_put_dirac_pixels32_sse2;
        c->avg_dirac_pixels_tab[2][0] = ff_avg_dirac_pixels32_sse2;
    }

    if (EXTERNAL_SSE4(mm_flags)) {
        c->dequant_subband[1]         = ff_dequant_subband_32_sse4;
        c->put_signed_rect_clamped[1] = ff_put_signed_rect_clamped_10_sse4;
    }
}