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
 int /*<<< orphan*/  arm11_setup_pmu ; 
 int em_call_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scu_setup () ; 

__attribute__((used)) static int em_setup_ctrs(void)
{
	int ret;

	/* Configure CPU counters by cross-calling to the other CPUs */
	ret = em_call_function(arm11_setup_pmu);
	if (ret == 0)
		scu_setup();

	return 0;
}