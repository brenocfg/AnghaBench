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
struct vcpu_svm {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_NRIPS ; 
 int emulate_on_interception (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_inject_gp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kvm_rdpmc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_emulated_instruction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdpmc_interception(struct vcpu_svm *svm)
{
	int err;

	if (!static_cpu_has(X86_FEATURE_NRIPS))
		return emulate_on_interception(svm);

	err = kvm_rdpmc(&svm->vcpu);
	if (err)
		kvm_inject_gp(&svm->vcpu, 0);
	else
		skip_emulated_instruction(&svm->vcpu);

	return 1;
}