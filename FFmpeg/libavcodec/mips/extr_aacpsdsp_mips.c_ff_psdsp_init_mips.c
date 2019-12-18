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
struct TYPE_3__ {int /*<<< orphan*/ * stereo_interpolate; int /*<<< orphan*/  decorrelate; int /*<<< orphan*/  mul_pair_single; int /*<<< orphan*/  add_squares; int /*<<< orphan*/  hybrid_synthesis_deint; int /*<<< orphan*/  hybrid_analysis_ileave; } ;
typedef  TYPE_1__ PSDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  ps_add_squares_mips ; 
 int /*<<< orphan*/  ps_decorrelate_mips ; 
 int /*<<< orphan*/  ps_hybrid_analysis_ileave_mips ; 
 int /*<<< orphan*/  ps_hybrid_synthesis_deint_mips ; 
 int /*<<< orphan*/  ps_mul_pair_single_mips ; 
 int /*<<< orphan*/  ps_stereo_interpolate_mips ; 

void ff_psdsp_init_mips(PSDSPContext *s)
{
#if HAVE_INLINE_ASM
    s->hybrid_analysis_ileave = ps_hybrid_analysis_ileave_mips;
    s->hybrid_synthesis_deint = ps_hybrid_synthesis_deint_mips;
#if HAVE_MIPSFPU
#if !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    s->add_squares            = ps_add_squares_mips;
    s->mul_pair_single        = ps_mul_pair_single_mips;
    s->decorrelate            = ps_decorrelate_mips;
    s->stereo_interpolate[0]  = ps_stereo_interpolate_mips;
#endif /* !HAVE_MIPS32R6 && !HAVE_MIPS64R6 */
#endif /* HAVE_MIPSFPU */
#endif /* HAVE_INLINE_ASM */
}