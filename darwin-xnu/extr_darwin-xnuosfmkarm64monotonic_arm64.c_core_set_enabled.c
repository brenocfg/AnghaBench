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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR0 ; 
 int PMCR0_FIXED_EN ; 
 int PMCR0_INIT ; 
 int __builtin_arm_rsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_wsr64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
core_set_enabled(void)
{
	uint64_t pmcr0;

	pmcr0 = __builtin_arm_rsr64(PMCR0);
	pmcr0 |= PMCR0_INIT | PMCR0_FIXED_EN;
	__builtin_arm_wsr64(PMCR0, pmcr0);
}