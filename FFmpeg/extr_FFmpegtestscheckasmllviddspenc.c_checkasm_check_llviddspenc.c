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
typedef  int /*<<< orphan*/  LLVidEncDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  check_diff_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_sub_left_pred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_llvidencdsp_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_llviddspenc(void)
{
    LLVidEncDSPContext c;
    ff_llvidencdsp_init(&c);

    check_diff_bytes(&c);
    report("diff_bytes");

    check_sub_left_pred(&c);
    report("sub_left_predict");
}