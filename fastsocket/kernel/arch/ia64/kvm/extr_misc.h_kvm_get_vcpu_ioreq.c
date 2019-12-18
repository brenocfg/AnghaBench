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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmio_req {int dummy; } ;
struct TYPE_2__ {struct kvm_mmio_req ioreq; } ;
struct exit_ctl_data {scalar_t__ exit_reason; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_MMIO_INSTRUCTION ; 
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 

__attribute__((used)) static inline struct kvm_mmio_req *kvm_get_vcpu_ioreq(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p_ctl_data;

	if (vcpu) {
		p_ctl_data = kvm_get_exit_data(vcpu);
		if (p_ctl_data->exit_reason == EXIT_REASON_MMIO_INSTRUCTION)
			return &p_ctl_data->u.ioreq;
	}

	return NULL;
}