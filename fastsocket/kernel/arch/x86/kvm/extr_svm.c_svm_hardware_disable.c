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
 int /*<<< orphan*/  MSR_AMD64_TSC_RATIO ; 
 int /*<<< orphan*/  SVM_FEATURE_TSC_RATE ; 
 int /*<<< orphan*/  TSC_RATIO_DEFAULT ; 
 int /*<<< orphan*/  amd_pmu_disable_virt () ; 
 int /*<<< orphan*/  cpu_svm_disable () ; 
 scalar_t__ svm_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void svm_hardware_disable(void *garbage)
{
	/* Make sure we clean up behind us */
	if (svm_has(SVM_FEATURE_TSC_RATE))
		wrmsrl(MSR_AMD64_TSC_RATIO, TSC_RATIO_DEFAULT);

	cpu_svm_disable();

	amd_pmu_disable_virt();
}