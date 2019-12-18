#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int cpsr; void* pc; void* sp; void* lr; void* fp; void** x; } ;
typedef  TYPE_1__ dbgwrap_thread_state_t ;
typedef  int /*<<< orphan*/  dbgwrap_status_t ;
struct TYPE_9__ {scalar_t__* coresight_base; } ;
typedef  TYPE_2__ cpu_data_t ;

/* Variables and functions */
 int ARM_DBG_LOCK_ACCESS_KEY ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGLAR ; 
 size_t CORESIGHT_ED ; 
 int /*<<< orphan*/  DBGWRAP_ERR_UNSUPPORTED ; 
 int /*<<< orphan*/  DBGWRAP_WARN_CPU_OFFLINE ; 
 int volatile EDPRSR_OSLK ; 
 scalar_t__ EDPRSR_REG_OFFSET ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_2__* cpu_datap (int) ; 
 int /*<<< orphan*/  ml_dbgwrap_halt_cpu (int,int /*<<< orphan*/ ) ; 
 void* ml_dbgwrap_read_dtr (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_dbgwrap_stuff_instr (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

dbgwrap_status_t
ml_dbgwrap_halt_cpu_with_state(int cpu_index, uint64_t timeout_ns, dbgwrap_thread_state_t *state)
{
	cpu_data_t *cdp = cpu_datap(cpu_index);
	if ((cdp == NULL) || (cdp->coresight_base[CORESIGHT_ED] == 0))
		return DBGWRAP_ERR_UNSUPPORTED;

	/* Ensure memory-mapped coresight registers can be written */
	*((volatile uint32_t *)(cdp->coresight_base[CORESIGHT_ED] + ARM_DEBUG_OFFSET_DBGLAR)) = ARM_DBG_LOCK_ACCESS_KEY;

	dbgwrap_status_t status = ml_dbgwrap_halt_cpu(cpu_index, timeout_ns);

	/* A core that is not fully powered (e.g. idling in wfi) can still be halted; the dbgwrap
	 * register and certain coresight registers such EDPRSR are in the always-on domain.
	 * However, EDSCR/EDITR are not in the always-on domain and will generate a parity abort
	 * on read.  EDPRSR can be safely read in all cases, and the OS lock defaults to being set
	 * but we clear it first thing, so use that to detect the offline state. */
	if (*((volatile uint32_t *)(cdp->coresight_base[CORESIGHT_ED] + EDPRSR_REG_OFFSET)) & EDPRSR_OSLK) {
		bzero(state, sizeof(*state));
		return DBGWRAP_WARN_CPU_OFFLINE;
	}

	uint32_t instr;

	for (unsigned int i = 0; i < (sizeof(state->x) / sizeof(state->x[0])); ++i) {
		instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | i; // msr DBGDTR0, x<i>
		ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
		state->x[i] = ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);
	}

	instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | 29; // msr DBGDTR0, fp
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	state->fp = ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);

	instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | 30; // msr DBGDTR0, lr
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	state->lr = ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);

	/* Stack pointer (x31) can't be used as a register operand for msr; register 31 is treated as xzr
	 * rather than sp when used as the transfer operand there.  Instead, load sp into a GPR
	 * we've already saved off and then store that register in the DTR.  I've chosen x18
	 * as the temporary GPR since it's reserved by the arm64 ABI and unused by xnu, so overwriting
	 * it poses the least risk of causing trouble for external debuggers. */ 

	instr = (0x91U << 24) | (31 << 5) | 18; // mov x18, sp
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | 18; // msr DBGDTR0, x18
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	state->sp = ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);

	/* reading PC (e.g. through adr) is undefined in debug state.  Instead use DLR_EL0,
	 * which contains PC at time of entry into debug state.*/

	instr = (0xD53U << 20) | (1 << 19) | (3 << 16) | (4 << 12) | (5 << 8) | (1 << 5) | 18; // mrs    x18, DLR_EL0
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | 18; // msr DBGDTR0, x18
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	state->pc = ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);

	/* reading CPSR is undefined in debug state.  Instead use DSPSR_EL0,
	 * which contains CPSR at time of entry into debug state.*/
	instr = (0xD53U << 20) | (1 << 19) | (3 << 16) | (4 << 12) | (5 << 8) | 18; // mrs    x18, DSPSR_EL0
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	instr = (0xD51U << 20) | (2 << 19) | (3 << 16) | (4 << 8) | 18; // msr DBGDTR0, x18
	ml_dbgwrap_stuff_instr(cdp, instr, timeout_ns, &status);
	state->cpsr = (uint32_t)ml_dbgwrap_read_dtr(cdp, timeout_ns, &status);

	return status;
}