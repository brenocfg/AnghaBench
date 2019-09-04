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
typedef  int /*<<< orphan*/  LLVidDSPContext ;

/* Variables and functions */
 int av_clip (int,int,int) ; 
 int /*<<< orphan*/  check_add_bytes (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_add_gradient_pred (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_add_left_pred (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  check_add_left_pred_16 (int /*<<< orphan*/ ,int,int,int,char*) ; 
 int /*<<< orphan*/  check_add_median_pred (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_llviddsp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report (char*) ; 
 int rnd () ; 

void checkasm_check_llviddsp(void)
{
    LLVidDSPContext c;
    int width = 16 * av_clip(rnd(), 16, 128);
    int accRnd = rnd() & 0xFF;

    ff_llviddsp_init(&c);

    check_add_bytes(c, width);
    report("add_bytes");

    check_add_median_pred(c, width);
    report("add_median_pred");

    check_add_left_pred(c, width, 0, "add_left_pred_zero");
    report("add_left_pred_zero");

    check_add_left_pred(c, width, accRnd, "add_left_pred_rnd_acc");
    report("add_left_pred_rnd_acc");

    check_add_left_pred_16(c, 255, width, accRnd, "add_left_pred_int16");
    report("add_left_pred_int16");

    check_add_gradient_pred(c, width);
    report("add_gradient_pred");
}