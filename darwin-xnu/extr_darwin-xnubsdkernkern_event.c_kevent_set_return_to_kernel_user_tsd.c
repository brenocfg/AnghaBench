#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {int /*<<< orphan*/ * uu_kqr_bound; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_flag; int p_pid; } ;

/* Variables and functions */
 int P_LP64 ; 
 int R2K_WORKLOOP_PENDING_EVENTS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int) ; 
 int thread_rettokern_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kevent_set_return_to_kernel_user_tsd(proc_t p, thread_t thread)
{
	uint64_t ast_addr;
	bool proc_is_64bit = !!(p->p_flag & P_LP64);
	size_t user_addr_size = proc_is_64bit ? 8 : 4;
	uint32_t ast_flags32 = 0;
	uint64_t ast_flags64 = 0;
	struct uthread *ut = get_bsdthread_info(thread);

	if (ut->uu_kqr_bound != NULL) {
		ast_flags64 |= R2K_WORKLOOP_PENDING_EVENTS;
	}

	if (ast_flags64 == 0) {
		return;
	}

	if (!(p->p_flag & P_LP64)) {
		ast_flags32 = (uint32_t)ast_flags64;
		assert(ast_flags64 < 0x100000000ull);
	}

	ast_addr = thread_rettokern_addr(thread);
	if (ast_addr == 0) {
		return;
	}

	if (copyout((proc_is_64bit ? (void *)&ast_flags64 : (void *)&ast_flags32),
	            (user_addr_t)ast_addr,
	            user_addr_size) != 0) {
		printf("pid %d (tid:%llu): copyout of return_to_kernel ast flags failed with "
		       "ast_addr = %llu\n", p->p_pid, thread_tid(current_thread()), ast_addr);
	}
}