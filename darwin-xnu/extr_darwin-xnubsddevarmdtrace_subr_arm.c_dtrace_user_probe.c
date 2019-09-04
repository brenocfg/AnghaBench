#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  void* user_addr_t ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  lck_rw_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_11__ {int cpsr; void* pc; } ;
typedef  TYPE_2__ arm_saved_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  cpu_ft_lock; } ;
struct TYPE_10__ {scalar_t__ t_dtrace_step; scalar_t__ t_dtrace_ret; scalar_t__ t_dtrace_ft; scalar_t__ t_dtrace_ast; void* t_dtrace_npc; } ;

/* Variables and functions */
 TYPE_9__* CPU ; 
 scalar_t__ FASTTRAP_ARM_INSTR ; 
 scalar_t__ FASTTRAP_ARM_RET_INSTR ; 
 scalar_t__ FASTTRAP_THUMB_INSTR ; 
 scalar_t__ FASTTRAP_THUMB_RET_INSTR ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PSR_TF ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_pid_probe_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_return_probe_ptr (TYPE_2__*) ; 
 scalar_t__ fuword16 (void*,scalar_t__*) ; 
 scalar_t__ fuword32 (void*,scalar_t__*) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_uthread_update (TYPE_1__*,struct proc*) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ stub2 (TYPE_2__*) ; 

kern_return_t
dtrace_user_probe(arm_saved_state_t *regs, unsigned int instr)
{
	/*
	 * FIXME
	 *
	 * The only call path into this method is always a user trap.
	 * We don't need to test for user trap, but should assert it.
	 */

	lck_rw_t *rwp;
	struct proc *p = current_proc();

	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

	kauth_cred_uthread_update(uthread, p);

	if (((regs->cpsr & PSR_TF) && ((uint16_t) instr) == FASTTRAP_THUMB_RET_INSTR) ||
	    ((uint32_t) instr == FASTTRAP_ARM_RET_INSTR)) {
		uint8_t step = uthread->t_dtrace_step;
		uint8_t ret = uthread->t_dtrace_ret;
		user_addr_t npc = uthread->t_dtrace_npc;

		if (uthread->t_dtrace_ast) {
			printf("dtrace_user_probe() should be calling aston()\n");
			// aston(thread);
			// uthread->t_sig_check = 1;
		}

		/*
		 * Clear all user tracing flags.
		 */
		uthread->t_dtrace_ft = 0;

		/*
		 * If we weren't expecting to take a return probe trap, kill
		 * the process as though it had just executed an unassigned
		 * trap instruction.
		 */
		if (step == 0) {
			/*
			 * APPLE NOTE: We're returning KERN_FAILURE, which causes 
			 * the generic signal handling code to take over, which will effectively
			 * deliver a EXC_BAD_INSTRUCTION to the user process.
			 */
			return KERN_FAILURE;
		} 

		/*
		 * If we hit this trap unrelated to a return probe, we're
		 * just here to reset the AST flag since we deferred a signal
		 * until after we logically single-stepped the instruction we
		 * copied out.
		 */
		if (ret == 0) {
			regs->pc = npc;
			return KERN_SUCCESS;
		}

		/*
		 * We need to wait until after we've called the
		 * dtrace_return_probe_ptr function pointer to step the pc.
		 */
		rwp = &CPU->cpu_ft_lock;
		lck_rw_lock_shared(rwp);

		if (dtrace_return_probe_ptr != NULL)
			(void) (*dtrace_return_probe_ptr)(regs);
		lck_rw_unlock_shared(rwp);

		regs->pc = npc;

		return KERN_SUCCESS;
	} else {
		rwp = &CPU->cpu_ft_lock;

		/*
		 * The DTrace fasttrap provider uses a trap,
		 * FASTTRAP_{ARM,THUMB}_INSTR. We let
		 * DTrace take the first crack at handling
		 * this trap; if it's not a probe that DTrace knows about,
		 * we call into the trap() routine to handle it like a
		 * breakpoint placed by a conventional debugger.
		 */

		/*
		 * APPLE NOTE: I believe the purpose of the reader/writers lock
		 * is thus: There are times which dtrace needs to prevent calling
		 * dtrace_pid_probe_ptr(). Sun's original impl grabbed a plain
		 * mutex here. However, that serialized all probe calls, and
		 * destroyed MP behavior. So now they use a RW lock, with probes
		 * as readers, and the top level synchronization as a writer.
		 */
		lck_rw_lock_shared(rwp);
		if (dtrace_pid_probe_ptr != NULL &&
		    (*dtrace_pid_probe_ptr)(regs) == 0) {
			lck_rw_unlock_shared(rwp);
			return KERN_SUCCESS;
		}
		lck_rw_unlock_shared(rwp);

		/*
		 * If the instruction that caused the breakpoint trap doesn't
		 * look like our trap anymore, it may be that this tracepoint
		 * was removed just after the user thread executed it. In
		 * that case, return to user land to retry the instuction.
		 *
		 * Note that the PC points to the instruction that caused the fault.
		 */
		if (regs->cpsr & PSR_TF) {
			uint16_t instr_check;
			if (fuword16(regs->pc, &instr_check) == 0 && instr_check != FASTTRAP_THUMB_INSTR) {
				return KERN_SUCCESS;
			}
		} else {
			uint32_t instr_check;
			if (fuword32(regs->pc, &instr_check) == 0 && instr_check != FASTTRAP_ARM_INSTR) {
				return KERN_SUCCESS;
			}
		}
	}

	return KERN_FAILURE;
}