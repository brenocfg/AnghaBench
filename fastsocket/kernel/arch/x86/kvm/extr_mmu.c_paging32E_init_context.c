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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT32E_ROOT_LEVEL ; 
 int paging64_init_context_common (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int paging32E_init_context(struct kvm_vcpu *vcpu)
{
	reset_rsvds_bits_mask(vcpu, PT32E_ROOT_LEVEL);
	return paging64_init_context_common(vcpu, PT32E_ROOT_LEVEL);
}