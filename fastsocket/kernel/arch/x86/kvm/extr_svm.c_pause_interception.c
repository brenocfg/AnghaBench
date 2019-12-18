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
 int /*<<< orphan*/  kvm_vcpu_on_spin (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pause_interception(struct vcpu_svm *svm)
{
	kvm_vcpu_on_spin(&(svm->vcpu));
	return 1;
}