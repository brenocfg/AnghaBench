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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR1 ; 
 int /*<<< orphan*/  PMCR1_INIT ; 
 int /*<<< orphan*/  __builtin_arm_rsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_wsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
core_init_execution_modes(void)
{
	uint64_t pmcr1;

	pmcr1 = __builtin_arm_rsr64(PMCR1);
	pmcr1 |= PMCR1_INIT;
	__builtin_arm_wsr64(PMCR1, pmcr1);
}