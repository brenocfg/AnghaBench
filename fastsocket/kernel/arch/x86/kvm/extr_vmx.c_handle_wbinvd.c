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
 int /*<<< orphan*/  skip_emulated_instruction (struct kvm_vcpu*) ; 

__attribute__((used)) static int handle_wbinvd(struct kvm_vcpu *vcpu)
{
	skip_emulated_instruction(vcpu);
	/* TODO: Add support for VT-d/pass-through device */
	return 1;
}