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
 int /*<<< orphan*/  check_idct_dc4 () ; 
 int /*<<< orphan*/  check_loopfilter_16y () ; 
 int /*<<< orphan*/  check_loopfilter_8uv () ; 
 int /*<<< orphan*/  check_loopfilter_simple () ; 
 int /*<<< orphan*/  check_luma_dc_wht () ; 
 int /*<<< orphan*/  check_mc () ; 
 int /*<<< orphan*/  report (char*) ; 

void checkasm_check_vp8dsp(void)
{
    check_idct();
    check_idct_dc4();
    check_luma_dc_wht();
    report("idct");
    check_mc();
    report("mc");
    check_loopfilter_16y();
    check_loopfilter_8uv();
    check_loopfilter_simple();
    report("loopfilter");
}