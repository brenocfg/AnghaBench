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
union ia64_rr {scalar_t__ val; int /*<<< orphan*/  rid; int /*<<< orphan*/  ps; } ;
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ vcpu_get_rr (struct kvm_vcpu*,scalar_t__) ; 

__attribute__((used)) static u64 vcpu_get_itir_on_fault(struct kvm_vcpu *vcpu, u64 ifa)
{
	union ia64_rr rr, rr1;

	rr.val = vcpu_get_rr(vcpu, ifa);
	rr1.val = 0;
	rr1.ps = rr.ps;
	rr1.rid = rr.rid;
	return (rr1.val);
}