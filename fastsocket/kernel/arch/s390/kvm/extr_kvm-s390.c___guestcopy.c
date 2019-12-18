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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int copy_to_guest (struct kvm_vcpu*,int /*<<< orphan*/ ,void const*,unsigned long) ; 
 int copy_to_guest_absolute (struct kvm_vcpu*,int /*<<< orphan*/ ,void const*,unsigned long) ; 

__attribute__((used)) static int __guestcopy(struct kvm_vcpu *vcpu, u64 guestdest, const void *from,
		       unsigned long n, int prefix)
{
	if (prefix)
		return copy_to_guest(vcpu, guestdest, from, n);
	else
		return copy_to_guest_absolute(vcpu, guestdest, from, n);
}