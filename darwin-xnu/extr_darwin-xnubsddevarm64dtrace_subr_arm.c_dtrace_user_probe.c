#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  lck_rw_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  cpu_ft_lock; } ;
struct TYPE_8__ {int cpsr; scalar_t__ pc; } ;
struct TYPE_7__ {scalar_t__ pc; } ;
struct TYPE_6__ {scalar_t__ t_dtrace_step; scalar_t__ t_dtrace_ret; scalar_t__ t_dtrace_ft; scalar_t__ t_dtrace_ast; int /*<<< orphan*/  t_dtrace_npc; } ;

/* Variables and functions */
 TYPE_5__* CPU ; 
 scalar_t__ FASTTRAP_ARM32_INSTR ; 
 scalar_t__ FASTTRAP_ARM32_RET_INSTR ; 
 scalar_t__ FASTTRAP_ARM64_INSTR ; 
 scalar_t__ FASTTRAP_ARM64_RET_INSTR ; 
 scalar_t__ FASTTRAP_THUMB32_INSTR ; 
 scalar_t__ FASTTRAP_THUMB32_RET_INSTR ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int PSR_TF ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ dtrace_pid_probe_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_return_probe_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ fuword16 (scalar_t__,scalar_t__*) ; 
 scalar_t__ fuword32 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ is_saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_cred_uthread_update (TYPE_1__*,struct proc*) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_3__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_2__* saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_saved_state_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *) ; 

kern_return_t
dtrace_user_probe(arm_saved_state_t *regs)
{
	/*
	 * FIXME
	 *
	 * The only call path into this method is always a user trap.
	 * We don't need to test for user trap, but should assert it.
	 */

	lck_rw_t *rwp;
	struct proc *p = current_proc();
	int is_fasttrap = 0;

	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

	kauth_cred_uthread_update(uthread, p);

	if (is_saved_state32(regs)) {
		if (saved_state32(regs)->cpsr & PSR_TF) {
			uint16_t pc;
			if (copyin((user_addr_t)saved_state32(regs)->pc, &pc, sizeof(uint16_t))) {
				return KERN_FAILURE;
			}
			is_fasttrap = (pc == FASTTRAP_THUMB32_RET_INSTR);
		} else {
			uint32_t pc;
			if (copyin((user_addr_t)saved_state32(regs)->pc, &pc, sizeof(uint32_t))) {
				return KERN_FAILURE;
			}
			is_fasttrap = (pc == FASTTRAP_ARM32_RET_INSTR);
		}
	} else {
		uint32_t pc;
		if (copyin((user_addr_t)saved_state64(regs)->pc, &pc, sizeof(uint32_t))) {
			return KERN_FAILURE;
		}
		is_fasttrap = (pc == FASTTRAP_ARM64_RET_INSTR);
	}

	if (is_fasttrap) {
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
		 * If we weren't expecting a quick return to the kernel, just kill
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
		 * here to either:
		 *
		 * 1.  Reset the AST flag, since we deferred a signal
		 * until after we logically single-stepped the instruction we
		 * copied out.
		 *
		 * 2.  Just return to normal execution (required for U64).
		 */
		if (ret == 0) {
			set_saved_state_pc(regs, npc);
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

		set_saved_state_pc(regs, npc);

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
		if (is_saved_state32(regs)) {
			if (saved_state32(regs)->cpsr & PSR_TF) {
				uint16_t instr;
				if (fuword16(saved_state32(regs)->pc, &instr) == 0 && instr != FASTTRAP_THUMB32_INSTR) {
					return KERN_SUCCESS;
				}
			} else {
				uint32_t instr;
				if (fuword32(saved_state32(regs)->pc, &instr) == 0 && instr != FASTTRAP_ARM32_INSTR) {
					return KERN_SUCCESS;
				}
			}
		} else {
			uint32_t instr;
			if (fuword32(saved_state64(regs)->pc, &instr) == 0 && instr != FASTTRAP_ARM64_INSTR) {
				return KERN_SUCCESS;
			}
		}
	}

	return KERN_FAILURE;
}