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
typedef  size_t u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 struct kvm_vcpu* current_vcpu ; 
 int /*<<< orphan*/  panic_vm (struct kvm_vcpu*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vec2off ; 
 scalar_t__ vmm_sanity ; 

void vmm_panic_handler(u64 vec)
{
	struct kvm_vcpu *vcpu = current_vcpu;
	vmm_sanity = 0;
	panic_vm(vcpu, "Unexpected interruption occurs in VMM, vector:0x%lx\n",
			vec2off[vec]);
}