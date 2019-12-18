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

/* Variables and functions */
 scalar_t__ PARAVIRT_LAZY_NONE ; 
 int /*<<< orphan*/  async_hcall (unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_hypercall3 (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ paravirt_get_lazy_mode () ; 

__attribute__((used)) static void lazy_hcall3(unsigned long call,
		       unsigned long arg1,
		       unsigned long arg2,
		       unsigned long arg3)
{
	if (paravirt_get_lazy_mode() == PARAVIRT_LAZY_NONE)
		kvm_hypercall3(call, arg1, arg2, arg3);
	else
		async_hcall(call, arg1, arg2, arg3, 0);
}