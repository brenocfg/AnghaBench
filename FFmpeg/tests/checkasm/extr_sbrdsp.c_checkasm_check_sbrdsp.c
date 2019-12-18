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
struct TYPE_4__ {int /*<<< orphan*/  hf_g_filt; int /*<<< orphan*/  hf_gen; int /*<<< orphan*/  autocorrelate; int /*<<< orphan*/  qmf_deint_bfly; int /*<<< orphan*/  qmf_deint_neg; int /*<<< orphan*/  qmf_post_shuffle; int /*<<< orphan*/  qmf_pre_shuffle; int /*<<< orphan*/  neg_odd_64; int /*<<< orphan*/  sum_square; int /*<<< orphan*/  sum64x5; } ;
typedef  TYPE_1__ SBRDSPContext ;

/* Variables and functions */
 scalar_t__ check_func (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_sbrdsp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  test_autocorrelate () ; 
 int /*<<< orphan*/  test_hf_apply_noise (TYPE_1__*) ; 
 int /*<<< orphan*/  test_hf_g_filt () ; 
 int /*<<< orphan*/  test_hf_gen () ; 
 int /*<<< orphan*/  test_neg_odd_64 () ; 
 int /*<<< orphan*/  test_qmf_deint_bfly () ; 
 int /*<<< orphan*/  test_qmf_deint_neg () ; 
 int /*<<< orphan*/  test_qmf_post_shuffle () ; 
 int /*<<< orphan*/  test_qmf_pre_shuffle () ; 
 int /*<<< orphan*/  test_sum64x5 () ; 
 int /*<<< orphan*/  test_sum_square () ; 

void checkasm_check_sbrdsp(void)
{
    SBRDSPContext sbrdsp;

    ff_sbrdsp_init(&sbrdsp);

    if (check_func(sbrdsp.sum64x5, "sum64x5"))
        test_sum64x5();
    report("sum64x5");

    if (check_func(sbrdsp.sum_square, "sum_square"))
        test_sum_square();
    report("sum_square");

    if (check_func(sbrdsp.neg_odd_64, "neg_odd_64"))
        test_neg_odd_64();
    report("neg_odd_64");

    if (check_func(sbrdsp.qmf_pre_shuffle, "qmf_pre_shuffle"))
        test_qmf_pre_shuffle();
    report("qmf_pre_shuffle");

    if (check_func(sbrdsp.qmf_post_shuffle, "qmf_post_shuffle"))
        test_qmf_post_shuffle();
    report("qmf_post_shuffle");

    if (check_func(sbrdsp.qmf_deint_neg, "qmf_deint_neg"))
        test_qmf_deint_neg();
    report("qmf_deint_neg");

    if (check_func(sbrdsp.qmf_deint_bfly, "qmf_deint_bfly"))
        test_qmf_deint_bfly();
    report("qmf_deint_bfly");

    if (check_func(sbrdsp.autocorrelate, "autocorrelate"))
        test_autocorrelate();
    report("autocorrelate");

    if (check_func(sbrdsp.hf_gen, "hf_gen"))
        test_hf_gen();
    report("hf_gen");

    if (check_func(sbrdsp.hf_g_filt, "hf_g_filt"))
        test_hf_g_filt();
    report("hf_g_filt");

    test_hf_apply_noise(&sbrdsp);
    report("hf_apply_noise");
}