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
typedef  union context {int dummy; } context ;
struct TYPE_2__ {union context guest; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;

/* Variables and functions */
 union context* to_guest (int /*<<< orphan*/ ,union context*) ; 

__attribute__((used)) static inline union context *kvm_get_guest_context(struct kvm_vcpu *vcpu)
{
	union context *ctx = &vcpu->arch.guest;
	return  to_guest(vcpu->kvm, ctx);
}