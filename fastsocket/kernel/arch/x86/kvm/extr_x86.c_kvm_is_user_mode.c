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
struct TYPE_2__ {int (* get_cpl ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  current_vcpu ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ percpu_read (int /*<<< orphan*/ ) ; 
 int stub1 (scalar_t__) ; 

__attribute__((used)) static int kvm_is_user_mode(void)
{
	int user_mode = 3;

	if (percpu_read(current_vcpu))
		user_mode = kvm_x86_ops->get_cpl(percpu_read(current_vcpu));

	return user_mode != 0;
}