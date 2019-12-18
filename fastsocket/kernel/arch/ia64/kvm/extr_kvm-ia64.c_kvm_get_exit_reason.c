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
typedef  int /*<<< orphan*/  uint32_t ;
struct kvm_vcpu {int dummy; } ;
struct exit_ctl_data {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 struct exit_ctl_data* kvm_get_exit_data (struct kvm_vcpu*) ; 

__attribute__((used)) static uint32_t kvm_get_exit_reason(struct kvm_vcpu *vcpu)
{
	struct exit_ctl_data *p_exit_data;

	p_exit_data = kvm_get_exit_data(vcpu);
	return p_exit_data->exit_reason;
}