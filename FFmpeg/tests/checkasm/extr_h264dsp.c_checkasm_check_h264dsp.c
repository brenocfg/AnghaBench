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

/* Variables and functions */
 int /*<<< orphan*/  check_idct () ; 
 int /*<<< orphan*/  check_idct_multiple () ; 
 int /*<<< orphan*/  check_loop_filter () ; 
 int /*<<< orphan*/  check_loop_filter_intra () ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_h264dsp(void)
{
    check_idct();
    check_idct_multiple();
    report("idct");

    check_loop_filter();
    report("loop_filter");

    check_loop_filter_intra();
    report("loop_filter_intra");
}