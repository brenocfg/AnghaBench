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
typedef  int u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int vcpu_tsc_khz (struct kvm_vcpu*) ; 

__attribute__((used)) static inline u64 nsec_to_cycles(struct kvm_vcpu *vcpu, u64 nsec)
{
	u64 ret;

	ret = nsec * vcpu_tsc_khz(vcpu);
	do_div(ret, USEC_PER_SEC);
	return ret;
}