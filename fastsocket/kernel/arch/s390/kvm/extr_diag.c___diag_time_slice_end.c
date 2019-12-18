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
struct TYPE_2__ {int /*<<< orphan*/  diagnose_44; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_EVENT (struct kvm_vcpu*,int,char*,char*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int __diag_time_slice_end(struct kvm_vcpu *vcpu)
{
	VCPU_EVENT(vcpu, 5, "%s", "diag time slice end");
	vcpu->stat.diagnose_44++;
	vcpu_put(vcpu);
	yield();
	vcpu_load(vcpu);
	return 0;
}