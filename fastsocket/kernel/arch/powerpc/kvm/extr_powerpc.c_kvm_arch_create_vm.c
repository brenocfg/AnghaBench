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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kvm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct kvm* kzalloc (int,int /*<<< orphan*/ ) ; 

struct kvm *kvm_arch_create_vm(void)
{
	struct kvm *kvm;

	kvm = kzalloc(sizeof(struct kvm), GFP_KERNEL);
	if (!kvm)
		return ERR_PTR(-ENOMEM);

	return kvm;
}