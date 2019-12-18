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
struct vcpu_svm {int /*<<< orphan*/  vcpu; scalar_t__ next_rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_gif (struct vcpu_svm*) ; 
 scalar_t__ kvm_rip_read (int /*<<< orphan*/ *) ; 
 scalar_t__ nested_svm_check_permissions (struct vcpu_svm*) ; 
 int /*<<< orphan*/  skip_emulated_instruction (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stgi_interception(struct vcpu_svm *svm)
{
	if (nested_svm_check_permissions(svm))
		return 1;

	svm->next_rip = kvm_rip_read(&svm->vcpu) + 3;
	skip_emulated_instruction(&svm->vcpu);

	enable_gif(svm);

	return 1;
}