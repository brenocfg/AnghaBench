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
struct TYPE_2__ {int /*<<< orphan*/  (* hardware_disable ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drop_user_return_notifiers (void*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void kvm_arch_hardware_disable(void *garbage)
{
	kvm_x86_ops->hardware_disable(garbage);
	drop_user_return_notifiers(garbage);
}