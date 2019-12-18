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
struct TYPE_2__ {int /*<<< orphan*/  is_sn2; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kvm* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct kvm*) ; 
 int /*<<< orphan*/  ia64_platform_is (char*) ; 
 struct kvm* kvm_alloc_kvm () ; 
 int /*<<< orphan*/  kvm_init_vm (struct kvm*) ; 

struct  kvm *kvm_arch_create_vm(void)
{
	struct kvm *kvm = kvm_alloc_kvm();

	if (IS_ERR(kvm))
		return ERR_PTR(-ENOMEM);

	kvm->arch.is_sn2 = ia64_platform_is("sn2");

	kvm_init_vm(kvm);

	return kvm;

}