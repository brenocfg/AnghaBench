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
typedef  int value ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_NHM_TURBO_RATIO_LIMIT ; 
 int intel_pstate_max_pstate () ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pstate_turbo_pstate(void)
{
	u64 value;
	int nont, ret;
	rdmsrl(MSR_NHM_TURBO_RATIO_LIMIT, value);
	nont = intel_pstate_max_pstate();
	ret = ((value) & 255);
	if (ret <= nont)
		ret = nont;
	return ret;
}