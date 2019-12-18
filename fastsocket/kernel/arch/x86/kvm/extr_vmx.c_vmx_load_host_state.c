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
struct vcpu_vmx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vmx_load_host_state (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static void vmx_load_host_state(struct vcpu_vmx *vmx)
{
	preempt_disable();
	__vmx_load_host_state(vmx);
	preempt_enable();
}