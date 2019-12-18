#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uthread_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_9__ {scalar_t__ ftt_type; int /*<<< orphan*/ * ftt_retids; } ;
typedef  TYPE_3__ fasttrap_tracepoint_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_8__ {scalar_t__ t_dtrace_astpc; scalar_t__ t_dtrace_scrpc; int t_dtrace_step; int t_dtrace_on; TYPE_1__* t_dtrace_scratch; scalar_t__ t_dtrace_npc; scalar_t__ t_dtrace_pc; int /*<<< orphan*/  t_dtrace_ret; } ;
struct TYPE_7__ {scalar_t__ addr; scalar_t__ write_addr; } ;

/* Variables and functions */
 int FASTTRAP_ARM64_RET_INSTR ; 
 scalar_t__ FASTTRAP_T_ARM64_RET ; 
 scalar_t__ FASTTRAP_T_ARM64_RETAB ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bcopy (int const*,int*,int) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 scalar_t__ get_saved_state_pc (int /*<<< orphan*/ *) ; 
 scalar_t__ uwrite (int /*<<< orphan*/ *,int*,int,scalar_t__) ; 

__attribute__((used)) static void
fasttrap_pid_probe_thunk_instr64(arm_saved_state_t *state, fasttrap_tracepoint_t *tp, proc_t *p, uthread_t uthread,
		const uint32_t *instructions, uint32_t num_instrs, user_addr_t *pc_out)
{
	uint32_t local_scratch[8];
	user_addr_t pc = get_saved_state_pc(state);
	user_addr_t user_scratch_area;

	assert(num_instrs < 8);

	bcopy(instructions, local_scratch, num_instrs * sizeof(uint32_t));
	local_scratch[num_instrs] = FASTTRAP_ARM64_RET_INSTR;

	uthread->t_dtrace_astpc = uthread->t_dtrace_scrpc = uthread->t_dtrace_scratch->addr;
	user_scratch_area = uthread->t_dtrace_scratch->write_addr;

	if (user_scratch_area == (user_addr_t)0) {
		fasttrap_sigtrap(p, uthread, pc); // Should be killing target proc
		*pc_out = pc;
		return;
	}

	if (uwrite(p, local_scratch, (num_instrs + 1) * sizeof(uint32_t), user_scratch_area) != KERN_SUCCESS) {
		fasttrap_sigtrap(p, uthread, pc);
		*pc_out = pc;
		return;
	}

	/* We're stepping (come back to kernel to adjust PC for return to regular code). */
	uthread->t_dtrace_step = 1;

	/* We may or may not be about to run a return probe (but we wouldn't thunk ret lr)*/
	uthread->t_dtrace_ret = (tp->ftt_retids != NULL);
	assert(tp->ftt_type != FASTTRAP_T_ARM64_RET);
	assert(tp->ftt_type != FASTTRAP_T_ARM64_RETAB);

	/* Set address of instruction we've patched */
	uthread->t_dtrace_pc = pc;

	/* Any branch would be emulated, next instruction should be one ahead */
	uthread->t_dtrace_npc = pc + 4;

	/* We are certainly handling a probe */
	uthread->t_dtrace_on = 1;

	/* Let's jump to the scratch area */
	*pc_out = uthread->t_dtrace_scratch->addr;
}