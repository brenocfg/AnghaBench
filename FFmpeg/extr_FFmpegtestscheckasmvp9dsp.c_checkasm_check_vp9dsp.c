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
 int /*<<< orphan*/  check_ipred () ; 
 int /*<<< orphan*/  check_itxfm () ; 
 int /*<<< orphan*/  check_loopfilter () ; 
 int /*<<< orphan*/  check_mc () ; 

void checkasm_check_vp9dsp(void)
{
    check_ipred();
    check_itxfm();
    check_loopfilter();
    check_mc();
}