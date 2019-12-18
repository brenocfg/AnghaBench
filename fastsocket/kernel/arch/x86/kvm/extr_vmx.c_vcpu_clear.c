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
struct TYPE_2__ {int cpu; } ;
struct vcpu_vmx {TYPE_1__ vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vcpu_clear ; 
 int /*<<< orphan*/  smp_call_function_single (int,int /*<<< orphan*/ ,struct vcpu_vmx*,int) ; 

__attribute__((used)) static void vcpu_clear(struct vcpu_vmx *vmx)
{
	if (vmx->vcpu.cpu == -1)
		return;
	smp_call_function_single(vmx->vcpu.cpu, __vcpu_clear, vmx, 1);
}