#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  __sa_handler; } ;
struct __user64_sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_tramp; TYPE_2__ __sigaction_u; } ;
struct TYPE_3__ {int /*<<< orphan*/  __sa_handler; } ;
struct __kern_sigaction {int /*<<< orphan*/  sa_tramp; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; TYPE_1__ __sigaction_u; } ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ machine_thread_function_pointers_convert_from_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
__sigaction_user64_to_kern(struct __user64_sigaction *in, struct __kern_sigaction *out)
{
	out->__sigaction_u.__sa_handler = in->__sigaction_u.__sa_handler;
	out->sa_tramp = in->sa_tramp;
	out->sa_mask = in->sa_mask;
	out->sa_flags = in->sa_flags;

	kern_return_t kr;
	kr = machine_thread_function_pointers_convert_from_user(current_thread(),
			&out->sa_tramp, 1);
	assert(kr == KERN_SUCCESS);
}