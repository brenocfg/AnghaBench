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
struct TYPE_2__ {scalar_t__ ptc_g_count; int /*<<< orphan*/ * ptc_g_data; } ;
struct kvm_vcpu {int /*<<< orphan*/  requests; TYPE_1__ arch; } ;
struct call_data {int /*<<< orphan*/  ptc_g_data; struct kvm_vcpu* vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_PTC_G ; 
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 scalar_t__ MAX_PTC_G_NUM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcpu_global_purge(void *info)
{
	struct call_data *p = (struct call_data *)info;
	struct kvm_vcpu *vcpu = p->vcpu;

	if (test_bit(KVM_REQ_TLB_FLUSH, &vcpu->requests))
		return;

	set_bit(KVM_REQ_PTC_G, &vcpu->requests);
	if (vcpu->arch.ptc_g_count < MAX_PTC_G_NUM) {
		vcpu->arch.ptc_g_data[vcpu->arch.ptc_g_count++] =
							p->ptc_g_data;
	} else {
		clear_bit(KVM_REQ_PTC_G, &vcpu->requests);
		vcpu->arch.ptc_g_count = 0;
		set_bit(KVM_REQ_TLB_FLUSH, &vcpu->requests);
	}
}