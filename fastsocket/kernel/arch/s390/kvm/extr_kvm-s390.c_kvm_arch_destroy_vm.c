#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dbf; scalar_t__ sca; } ;
struct kvm {int /*<<< orphan*/  srcu; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_physmem (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_vcpus (struct kvm*) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	kvm_free_vcpus(kvm);
	kvm_free_physmem(kvm);
	free_page((unsigned long)(kvm->arch.sca));
	debug_unregister(kvm->arch.dbf);
	cleanup_srcu_struct(&kvm->srcu);
	kfree(kvm);
}