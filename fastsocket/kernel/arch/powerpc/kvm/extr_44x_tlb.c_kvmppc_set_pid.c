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
typedef  scalar_t__ u32 ;
struct kvmppc_vcpu_44x {struct kvmppc_44x_shadow_ref* shadow_refs; } ;
struct kvmppc_44x_shadow_ref {scalar_t__ tid; } ;
struct TYPE_2__ {scalar_t__ pid; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvmppc_44x_shadow_ref*) ; 
 int /*<<< orphan*/  kvmppc_44x_shadow_release (struct kvmppc_vcpu_44x*,int) ; 
 struct kvmppc_vcpu_44x* to_44x (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

void kvmppc_set_pid(struct kvm_vcpu *vcpu, u32 new_pid)
{
	struct kvmppc_vcpu_44x *vcpu_44x = to_44x(vcpu);
	int i;

	if (unlikely(vcpu->arch.pid == new_pid))
		return;

	vcpu->arch.pid = new_pid;

	/* Guest userspace runs with TID=0 mappings and PID=0, to make sure it
	 * can't access guest kernel mappings (TID=1). When we switch to a new
	 * guest PID, which will also use host PID=0, we must discard the old guest
	 * userspace mappings. */
	for (i = 0; i < ARRAY_SIZE(vcpu_44x->shadow_refs); i++) {
		struct kvmppc_44x_shadow_ref *ref = &vcpu_44x->shadow_refs[i];

		if (ref->tid == 0)
			kvmppc_44x_shadow_release(vcpu_44x, i);
	}
}