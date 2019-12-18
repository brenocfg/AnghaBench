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
struct TYPE_4__ {int /*<<< orphan*/  hybrid_synthesis_deint; int /*<<< orphan*/  hybrid_analysis_ileave; int /*<<< orphan*/  hybrid_analysis; int /*<<< orphan*/  mul_pair_single; int /*<<< orphan*/  add_squares; } ;
typedef  TYPE_1__ PSDSPContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_psdsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  test_add_squares () ; 
 int /*<<< orphan*/  test_hybrid_analysis () ; 
 int /*<<< orphan*/  test_hybrid_analysis_ileave () ; 
 int /*<<< orphan*/  test_hybrid_synthesis_deint () ; 
 int /*<<< orphan*/  test_mul_pair_single () ; 
 int /*<<< orphan*/  test_stereo_interpolate (TYPE_1__*) ; 

void checkasm_check_aacpsdsp(void)
{
    PSDSPContext psdsp;

    ff_psdsp_init(&psdsp);

    if (check_func(psdsp.add_squares, "ps_add_squares"))
        test_add_squares();
    report("add_squares");

    if (check_func(psdsp.mul_pair_single, "ps_mul_pair_single"))
        test_mul_pair_single();
    report("mul_pair_single");

    if (check_func(psdsp.hybrid_analysis, "ps_hybrid_analysis"))
        test_hybrid_analysis();
    report("hybrid_analysis");

    if (check_func(psdsp.hybrid_analysis_ileave, "ps_hybrid_analysis_ileave"))
        test_hybrid_analysis_ileave();
    report("hybrid_analysis_ileave");

    if (check_func(psdsp.hybrid_synthesis_deint, "ps_hybrid_synthesis_deint"))
        test_hybrid_synthesis_deint();
    report("hybrid_synthesis_deint");

    test_stereo_interpolate(&psdsp);
    report("stereo_interpolate");
}