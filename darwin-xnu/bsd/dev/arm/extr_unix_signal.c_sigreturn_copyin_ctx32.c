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
typedef  int /*<<< orphan*/  user_addr_t ;
struct user_ucontext32 {int uc_mcsize; scalar_t__ uc_mcontext; } ;
typedef  struct user_ucontext32 mcontext32_t ;

/* Variables and functions */
 int EINVAL ; 
#define  UC_FLAVOR_SIZE32 128 
 int /*<<< orphan*/  assert (int) ; 
 int copyin (int /*<<< orphan*/ ,struct user_ucontext32*,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  proc_is64bit_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sigreturn_copyin_ctx32(struct user_ucontext32 *uctx, mcontext32_t *mctx, user_addr_t uctx_addr)
{
	int error;

	assert(!proc_is64bit_data(current_proc()));

	error = copyin(uctx_addr, uctx, sizeof(*uctx));
	if (error) {
		return (error);
	}

	/* validate the machine context size */
	switch (uctx->uc_mcsize) {
	case UC_FLAVOR_SIZE32:
		break;
	default:
		return (EINVAL);
	}

	assert(uctx->uc_mcsize == sizeof(*mctx));
	error = copyin((user_addr_t)uctx->uc_mcontext, mctx, uctx->uc_mcsize);
	if (error) {
		return (error);
	}

	return 0;
}