#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {unsigned long cr2; } ;
struct TYPE_3__ {int /*<<< orphan*/  pf_guest; } ;
struct kvm_vcpu {TYPE_2__ arch; TYPE_1__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_VECTOR ; 
 int /*<<< orphan*/  kvm_queue_exception_e (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_inject_page_fault(struct kvm_vcpu *vcpu, unsigned long addr,
			   u32 error_code)
{
	++vcpu->stat.pf_guest;
	vcpu->arch.cr2 = addr;
	kvm_queue_exception_e(vcpu, PF_VECTOR, error_code);
}