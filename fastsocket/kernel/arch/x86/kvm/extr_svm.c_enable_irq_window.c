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
struct vcpu_svm {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ gif_set (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nested_svm_intr (struct vcpu_svm*) ; 
 int /*<<< orphan*/  nsvm_printk (char*) ; 
 int /*<<< orphan*/  svm_inject_irq (struct vcpu_svm*,int) ; 
 int /*<<< orphan*/  svm_set_vintr (struct vcpu_svm*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void enable_irq_window(struct kvm_vcpu *vcpu)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	nsvm_printk("Trying to open IRQ window\n");

	nested_svm_intr(svm);

	/* In case GIF=0 we can't rely on the CPU to tell us when
	 * GIF becomes 1, because that's a separate STGI/VMRUN intercept.
	 * The next time we get that intercept, this function will be
	 * called again though and we'll get the vintr intercept. */
	if (gif_set(svm)) {
		svm_set_vintr(svm);
		svm_inject_irq(svm, 0x0);
	}
}