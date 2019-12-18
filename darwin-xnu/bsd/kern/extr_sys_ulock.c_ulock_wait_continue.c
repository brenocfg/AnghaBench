#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  TYPE_3__* uthread_t ;
struct TYPE_10__ {int /*<<< orphan*/  ull_turnstile; } ;
typedef  TYPE_4__ ull_t ;
typedef  int uint ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int int32_t ;
struct TYPE_7__ {int* retval; int flags; int /*<<< orphan*/  old_owner; int /*<<< orphan*/  owner_thread; } ;
struct TYPE_8__ {TYPE_1__ uus_ulock_wait_data; } ;
struct TYPE_9__ {TYPE_2__ uu_save; } ;

/* Variables and functions */
 int ULF_NO_ERRNO ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ull_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  ulock_wait_cleanup (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unix_syscall_return (int) ; 
 int wait_result_to_return_code (int /*<<< orphan*/ ) ; 

__attribute__((used)) __attribute__((noreturn))
static void
ulock_wait_continue(void * parameter, wait_result_t wr)
{
	thread_t self = current_thread();
	uthread_t uthread = (uthread_t)get_bsdthread_info(self);
	int ret = 0;

	ull_t *ull = (ull_t *)parameter;
	int32_t *retval = uthread->uu_save.uus_ulock_wait_data.retval;
	uint flags = uthread->uu_save.uus_ulock_wait_data.flags;
	thread_t owner_thread = uthread->uu_save.uus_ulock_wait_data.owner_thread;
	thread_t old_owner = uthread->uu_save.uus_ulock_wait_data.old_owner;

	ret = wait_result_to_return_code(wr);

	ull_lock(ull);
	turnstile_complete((uintptr_t)ull, &ull->ull_turnstile, NULL);

	ulock_wait_cleanup(ull, owner_thread, old_owner, retval);

	if ((flags & ULF_NO_ERRNO) && (ret != 0)) {
		*retval = -ret;
		ret = 0;
	}

	unix_syscall_return(ret);
}