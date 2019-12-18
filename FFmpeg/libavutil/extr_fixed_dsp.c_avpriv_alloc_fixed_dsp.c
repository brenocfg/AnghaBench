#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  scalarproduct_fixed; int /*<<< orphan*/  butterflies_fixed; int /*<<< orphan*/  vector_fmul_reverse; int /*<<< orphan*/  vector_fmul_add; int /*<<< orphan*/  vector_fmul; int /*<<< orphan*/  vector_fmul_window; int /*<<< orphan*/  vector_fmul_window_scaled; } ;
typedef  TYPE_1__ AVFixedDSPContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 TYPE_1__* av_malloc (int) ; 
 int /*<<< orphan*/  butterflies_fixed_c ; 
 int /*<<< orphan*/  ff_fixed_dsp_init_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  scalarproduct_fixed_c ; 
 int /*<<< orphan*/  vector_fmul_add_c ; 
 int /*<<< orphan*/  vector_fmul_c ; 
 int /*<<< orphan*/  vector_fmul_reverse_c ; 
 int /*<<< orphan*/  vector_fmul_window_c ; 
 int /*<<< orphan*/  vector_fmul_window_scaled_c ; 

AVFixedDSPContext * avpriv_alloc_fixed_dsp(int bit_exact)
{
    AVFixedDSPContext * fdsp = av_malloc(sizeof(AVFixedDSPContext));

    if (!fdsp)
        return NULL;

    fdsp->vector_fmul_window_scaled = vector_fmul_window_scaled_c;
    fdsp->vector_fmul_window = vector_fmul_window_c;
    fdsp->vector_fmul = vector_fmul_c;
    fdsp->vector_fmul_add = vector_fmul_add_c;
    fdsp->vector_fmul_reverse = vector_fmul_reverse_c;
    fdsp->butterflies_fixed = butterflies_fixed_c;
    fdsp->scalarproduct_fixed = scalarproduct_fixed_c;

    if (ARCH_X86)
        ff_fixed_dsp_init_x86(fdsp);

    return fdsp;
}