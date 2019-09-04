#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_24__ ;
typedef  struct TYPE_28__   TYPE_23__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_16__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_32__ {scalar_t__ eip; scalar_t__ uesp; int eax; int efl; int /*<<< orphan*/  ebp; int /*<<< orphan*/  ecx; } ;
typedef  TYPE_4__ x86_saved_state32_t ;
typedef  TYPE_5__* uthread_t ;
typedef  scalar_t__ user_addr_t ;
typedef  int uint_t ;
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  scratch ;
struct TYPE_34__ {int p_lflag; scalar_t__ p_pid; struct TYPE_34__* p_pptr; } ;
typedef  TYPE_6__ proc_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  lck_mtx_t ;
typedef  int /*<<< orphan*/  greg_t ;
struct TYPE_35__ {scalar_t__ ftt_pid; scalar_t__ ftt_pc; scalar_t__ ftt_size; int ftt_type; scalar_t__ ftt_dest; int ftt_code; scalar_t__ ftt_scale; int /*<<< orphan*/ * ftt_retids; int /*<<< orphan*/  ftt_instr; int /*<<< orphan*/  ftt_segment; int /*<<< orphan*/  ftt_index; int /*<<< orphan*/  ftt_base; TYPE_9__* ftt_ids; TYPE_1__* ftt_proc; struct TYPE_35__* ftt_next; } ;
typedef  TYPE_7__ fasttrap_tracepoint_t ;
struct TYPE_36__ {int ftp_id; int /*<<< orphan*/ * ftp_argmap; int /*<<< orphan*/  ftp_triggered; TYPE_2__* ftp_prov; } ;
typedef  TYPE_8__ fasttrap_probe_t ;
struct TYPE_37__ {scalar_t__ fti_ptype; TYPE_8__* fti_probe; struct TYPE_37__* fti_next; } ;
typedef  TYPE_9__ fasttrap_id_t ;
struct TYPE_25__ {TYPE_7__* ftb_data; } ;
typedef  TYPE_10__ fasttrap_bucket_t ;
typedef  int /*<<< orphan*/  dtrace_icookie_t ;
struct TYPE_33__ {int t_dtrace_step; int t_dtrace_on; scalar_t__ t_dtrace_pc; scalar_t__ t_dtrace_scrpc; scalar_t__ t_dtrace_astpc; int t_dtrace_ret; scalar_t__ t_dtrace_npc; TYPE_3__* t_dtrace_scratch; scalar_t__ t_dtrace_ft; } ;
struct TYPE_31__ {scalar_t__ addr; scalar_t__ write_addr; } ;
struct TYPE_30__ {scalar_t__ ftp_provider_type; } ;
struct TYPE_29__ {size_t cpu_id; } ;
struct TYPE_28__ {int /*<<< orphan*/  cpuc_pid_lock; } ;
struct TYPE_27__ {scalar_t__ ftpc_acount; } ;
struct TYPE_26__ {TYPE_10__* fth_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_24__* CPU ; 
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 scalar_t__ DTFTP_ENTRY ; 
 scalar_t__ DTFTP_IS_ENABLED ; 
 scalar_t__ DTFTP_PROVIDER_ONESHOT ; 
 int DTRACEFLT_UPRIV ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int FASTTRAP_EFLAGS_CF ; 
 int FASTTRAP_EFLAGS_OF ; 
 int FASTTRAP_EFLAGS_PF ; 
 int FASTTRAP_EFLAGS_SF ; 
 int FASTTRAP_EFLAGS_ZF ; 
 scalar_t__ FASTTRAP_INT ; 
#define  FASTTRAP_JA 156 
#define  FASTTRAP_JAE 155 
#define  FASTTRAP_JB 154 
#define  FASTTRAP_JBE 153 
#define  FASTTRAP_JE 152 
#define  FASTTRAP_JG 151 
#define  FASTTRAP_JGE 150 
#define  FASTTRAP_JL 149 
#define  FASTTRAP_JLE 148 
 scalar_t__ FASTTRAP_JMP32 ; 
#define  FASTTRAP_JNE 147 
#define  FASTTRAP_JNO 146 
#define  FASTTRAP_JNP 145 
#define  FASTTRAP_JNS 144 
#define  FASTTRAP_JO 143 
#define  FASTTRAP_JP 142 
#define  FASTTRAP_JS 141 
#define  FASTTRAP_LOOP 140 
#define  FASTTRAP_LOOPNZ 139 
#define  FASTTRAP_LOOPZ 138 
 int FASTTRAP_MAX_INSTR_SIZE ; 
 int /*<<< orphan*/  FASTTRAP_NOREG ; 
 int /*<<< orphan*/  FASTTRAP_SEG_NONE ; 
 size_t FASTTRAP_TPOINTS_INDEX (scalar_t__,scalar_t__) ; 
#define  FASTTRAP_T_CALL 137 
#define  FASTTRAP_T_COMMON 136 
#define  FASTTRAP_T_JCC 135 
#define  FASTTRAP_T_JCXZ 134 
#define  FASTTRAP_T_JMP 133 
#define  FASTTRAP_T_LOOP 132 
#define  FASTTRAP_T_NOP 131 
#define  FASTTRAP_T_PUSHL_EBP 130 
#define  FASTTRAP_T_RET 129 
#define  FASTTRAP_T_RET16 128 
 scalar_t__ ISSET (int,int /*<<< orphan*/ ) ; 
 int P_LINVFORK ; 
 int /*<<< orphan*/  P_LNOATTACH ; 
 scalar_t__ T_DTRACE_RET ; 
 scalar_t__ atomic_or_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_23__* cpu_core ; 
 TYPE_6__* current_proc () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  dtrace_interrupt_disable () ; 
 int /*<<< orphan*/  dtrace_interrupt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_probe (int,int,int,int,int,int) ; 
 int dtrace_probeid_error ; 
 int /*<<< orphan*/  fasttrap_copyout (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  fasttrap_do_seg (TYPE_7__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int fasttrap_fuword32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  fasttrap_fuword32_noerr (scalar_t__,int*) ; 
 scalar_t__ fasttrap_getreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fasttrap_return_common (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_sigsegv (TYPE_6__*,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  fasttrap_sigtrap (TYPE_6__*,TYPE_5__*,scalar_t__) ; 
 int fasttrap_suword32 (scalar_t__,int) ; 
 TYPE_16__ fasttrap_tpoints ; 
 int /*<<< orphan*/  fasttrap_tracepoint_retire (TYPE_6__*,TYPE_7__*) ; 
 int /*<<< orphan*/  fasttrap_usdt_args32 (TYPE_8__*,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  get_bsdthread_info (int /*<<< orphan*/ ) ; 
 int is_saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 TYPE_4__* saved_state32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fasttrap_pid_probe32(x86_saved_state_t *regs)
{
	ASSERT(is_saved_state32(regs));

	x86_saved_state32_t *regs32  = saved_state32(regs);
	user_addr_t pc = regs32->eip - 1;
	proc_t *p = current_proc();
	user_addr_t new_pc = 0;
	fasttrap_bucket_t *bucket;
	lck_mtx_t *pid_mtx;
	fasttrap_tracepoint_t *tp, tp_local;
	pid_t pid;
	dtrace_icookie_t cookie;
	uint_t is_enabled = 0, retire_tp = 1;

	uthread_t uthread = (uthread_t)get_bsdthread_info(current_thread());

	/*
	 * It's possible that a user (in a veritable orgy of bad planning)
	 * could redirect this thread's flow of control before it reached the
	 * return probe fasttrap. In this case we need to kill the process
	 * since it's in a unrecoverable state.
	 */
	if (uthread->t_dtrace_step) {
		ASSERT(uthread->t_dtrace_on);
		fasttrap_sigtrap(p, uthread, pc);
		return (0);
	}

	/*
	 * Clear all user tracing flags.
	 */
	uthread->t_dtrace_ft = 0;
	uthread->t_dtrace_pc = 0;
	uthread->t_dtrace_npc = 0;
	uthread->t_dtrace_scrpc = 0;
	uthread->t_dtrace_astpc = 0;

	/*
	 * Treat a child created by a call to vfork(2) as if it were its
	 * parent. We know that there's only one thread of control in such a
	 * process: this one.
	 */
	if (p->p_lflag & P_LINVFORK) {
		proc_list_lock();
		while (p->p_lflag & P_LINVFORK)
			p = p->p_pptr;
		proc_list_unlock();
	}

	pid = p->p_pid;
	pid_mtx = &cpu_core[CPU->cpu_id].cpuc_pid_lock;
	lck_mtx_lock(pid_mtx);
	bucket = &fasttrap_tpoints.fth_table[FASTTRAP_TPOINTS_INDEX(pid, pc)];

	/*
	 * Lookup the tracepoint that the process just hit.
	 */
	for (tp = bucket->ftb_data; tp != NULL; tp = tp->ftt_next) {
		if (pid == tp->ftt_pid && pc == tp->ftt_pc &&
		    tp->ftt_proc->ftpc_acount != 0)
			break;
	}

	/*
	 * If we couldn't find a matching tracepoint, either a tracepoint has
	 * been inserted without using the pid<pid> ioctl interface (see
	 * fasttrap_ioctl), or somehow we have mislaid this tracepoint.
	 */
	if (tp == NULL) {
		lck_mtx_unlock(pid_mtx);
		return (-1);
	}

	/*
	 * Set the program counter to the address of the traced instruction
	 * so that it looks right in ustack() output.
	 */
	regs32->eip = pc;

	if (tp->ftt_ids != NULL) {
		fasttrap_id_t *id;
		
		uint32_t s0, s1, s2, s3, s4, s5;
		uint32_t *stack = (uint32_t *)(uintptr_t)(regs32->uesp);
		
		/*
		 * In 32-bit mode, all arguments are passed on the
		 * stack. If this is a function entry probe, we need
		 * to skip the first entry on the stack as it
		 * represents the return address rather than a
		 * parameter to the function.
		 */
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[0], &s0);
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[1], &s1);
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[2], &s2);
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[3], &s3);
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[4], &s4);
		fasttrap_fuword32_noerr((user_addr_t)(unsigned long)&stack[5], &s5);
		
		for (id = tp->ftt_ids; id != NULL; id = id->fti_next) {
			fasttrap_probe_t *probe = id->fti_probe;
			
			if (ISSET(current_proc()->p_lflag, P_LNOATTACH)) {
				dtrace_probe(dtrace_probeid_error, 0 /* state */, probe->ftp_id, 
					     1 /* ndx */, -1 /* offset */, DTRACEFLT_UPRIV);
			} else {
				if (probe->ftp_prov->ftp_provider_type == DTFTP_PROVIDER_ONESHOT) {
					uint8_t already_triggered = atomic_or_8(&probe->ftp_triggered, 1);
					if (already_triggered) {
						continue;
					}
				}
				/*
				 * If we have at least one probe associated that
				 * is not a oneshot probe, don't remove the
				 * tracepoint
				 */
				else {
					retire_tp = 0;
				}
				if (id->fti_ptype == DTFTP_ENTRY) {
					/*
					 * We note that this was an entry
					 * probe to help ustack() find the
					 * first caller.
					 */
					cookie = dtrace_interrupt_disable();
					DTRACE_CPUFLAG_SET(CPU_DTRACE_ENTRY);
					dtrace_probe(probe->ftp_id, s1, s2,
						     s3, s4, s5);
					DTRACE_CPUFLAG_CLEAR(CPU_DTRACE_ENTRY);
					dtrace_interrupt_enable(cookie);
				} else if (id->fti_ptype == DTFTP_IS_ENABLED) {
					/*
					 * Note that in this case, we don't
					 * call dtrace_probe() since it's only
					 * an artificial probe meant to change
					 * the flow of control so that it
					 * encounters the true probe.
					 */
					is_enabled = 1;
				} else if (probe->ftp_argmap == NULL) {
					dtrace_probe(probe->ftp_id, s0, s1,
						     s2, s3, s4);
				} else {
					uint32_t t[5];

					fasttrap_usdt_args32(probe, regs32,
							     sizeof (t) / sizeof (t[0]), t);

					dtrace_probe(probe->ftp_id, t[0], t[1],
						     t[2], t[3], t[4]);
				}
			}
		}
		if (retire_tp) {
			fasttrap_tracepoint_retire(p, tp);
		}
	}

	/*
	 * We're about to do a bunch of work so we cache a local copy of
	 * the tracepoint to emulate the instruction, and then find the
	 * tracepoint again later if we need to light up any return probes.
	 */
	tp_local = *tp;
	lck_mtx_unlock(pid_mtx);
	tp = &tp_local;

	/*
	 * Set the program counter to appear as though the traced instruction
	 * had completely executed. This ensures that fasttrap_getreg() will
	 * report the expected value for REG_RIP.
	 */
	regs32->eip = pc + tp->ftt_size;

	/*
	 * If there's an is-enabled probe connected to this tracepoint it
	 * means that there was a 'xorl %eax, %eax' or 'xorq %rax, %rax'
	 * instruction that was placed there by DTrace when the binary was
	 * linked. As this probe is, in fact, enabled, we need to stuff 1
	 * into %eax or %rax. Accordingly, we can bypass all the instruction
	 * emulation logic since we know the inevitable result. It's possible
	 * that a user could construct a scenario where the 'is-enabled'
	 * probe was on some other instruction, but that would be a rather
	 * exotic way to shoot oneself in the foot.
	 */
	if (is_enabled) {
		regs32->eax = 1;
		new_pc = regs32->eip;
		goto done;
	}

	/*
	 * We emulate certain types of instructions to ensure correctness
	 * (in the case of position dependent instructions) or optimize
	 * common cases. The rest we have the thread execute back in user-
	 * land.
	 */
	switch (tp->ftt_type) {
		case FASTTRAP_T_RET:
		case FASTTRAP_T_RET16:
		{
			user_addr_t dst;
			user_addr_t addr;
			int ret;

			/*
			 * We have to emulate _every_ facet of the behavior of a ret
			 * instruction including what happens if the load from %esp
			 * fails; in that case, we send a SIGSEGV.
			 */
			uint32_t dst32;
			ret = fasttrap_fuword32((user_addr_t)regs32->uesp, &dst32);
			dst = dst32;
			addr = regs32->uesp + sizeof (uint32_t);

			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, (user_addr_t)regs32->uesp);
				new_pc = pc;
				break;
			}
			
			if (tp->ftt_type == FASTTRAP_T_RET16)
				addr += tp->ftt_dest;
			
			regs32->uesp = addr;
			new_pc = dst;
			break;
		}

		case FASTTRAP_T_JCC:
		{
			uint_t taken;
			
			switch (tp->ftt_code) {
				case FASTTRAP_JO:
					taken = (regs32->efl & FASTTRAP_EFLAGS_OF) != 0;
					break;
				case FASTTRAP_JNO:
					taken = (regs32->efl & FASTTRAP_EFLAGS_OF) == 0;
					break;
				case FASTTRAP_JB:
					taken = (regs32->efl & FASTTRAP_EFLAGS_CF) != 0;
					break;
				case FASTTRAP_JAE:
					taken = (regs32->efl & FASTTRAP_EFLAGS_CF) == 0;
					break;
				case FASTTRAP_JE:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) != 0;
					break;
				case FASTTRAP_JNE:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) == 0;
					break;
				case FASTTRAP_JBE:
					taken = (regs32->efl & FASTTRAP_EFLAGS_CF) != 0 ||
						(regs32->efl & FASTTRAP_EFLAGS_ZF) != 0;
					break;
				case FASTTRAP_JA:
					taken = (regs32->efl & FASTTRAP_EFLAGS_CF) == 0 &&
						(regs32->efl & FASTTRAP_EFLAGS_ZF) == 0;
					break;
				case FASTTRAP_JS:
					taken = (regs32->efl & FASTTRAP_EFLAGS_SF) != 0;
					break;
				case FASTTRAP_JNS:
					taken = (regs32->efl & FASTTRAP_EFLAGS_SF) == 0;
					break;
				case FASTTRAP_JP:
					taken = (regs32->efl & FASTTRAP_EFLAGS_PF) != 0;
					break;
				case FASTTRAP_JNP:
					taken = (regs32->efl & FASTTRAP_EFLAGS_PF) == 0;
					break;
				case FASTTRAP_JL:
					taken = ((regs32->efl & FASTTRAP_EFLAGS_SF) == 0) !=
						((regs32->efl & FASTTRAP_EFLAGS_OF) == 0);
					break;
				case FASTTRAP_JGE:
					taken = ((regs32->efl & FASTTRAP_EFLAGS_SF) == 0) ==
						((regs32->efl & FASTTRAP_EFLAGS_OF) == 0);
					break;
				case FASTTRAP_JLE:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) != 0 ||
						((regs32->efl & FASTTRAP_EFLAGS_SF) == 0) !=
						((regs32->efl & FASTTRAP_EFLAGS_OF) == 0);
					break;
				case FASTTRAP_JG:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) == 0 &&
						((regs32->efl & FASTTRAP_EFLAGS_SF) == 0) ==
						((regs32->efl & FASTTRAP_EFLAGS_OF) == 0);
					break;
				default:
					taken = FALSE;
			}
			
			if (taken)
				new_pc = tp->ftt_dest;
			else
				new_pc = pc + tp->ftt_size;
			break;
		}

		case FASTTRAP_T_LOOP:
		{
			uint_t taken;
			greg_t cx = regs32->ecx--;

			switch (tp->ftt_code) {
				case FASTTRAP_LOOPNZ:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) == 0 &&
						cx != 0;
					break;
				case FASTTRAP_LOOPZ:
					taken = (regs32->efl & FASTTRAP_EFLAGS_ZF) != 0 &&
						cx != 0;
					break;
				case FASTTRAP_LOOP:
					taken = (cx != 0);
					break;
				default:
					taken = FALSE;
			}
			
			if (taken)
				new_pc = tp->ftt_dest;
			else
				new_pc = pc + tp->ftt_size;
			break;
		}

		case FASTTRAP_T_JCXZ:
		{
			greg_t cx = regs32->ecx;
			
			if (cx == 0)
				new_pc = tp->ftt_dest;
			else
				new_pc = pc + tp->ftt_size;
			break;
		}

		case FASTTRAP_T_PUSHL_EBP:
		{
			user_addr_t addr = regs32->uesp - sizeof (uint32_t);
			int ret = fasttrap_suword32(addr, (uint32_t)regs32->ebp);
			
			if (ret == -1) {
				fasttrap_sigsegv(p, uthread, addr);
				new_pc = pc;
				break;
			}
			
			regs32->uesp = addr;
			new_pc = pc + tp->ftt_size;
			break;
		}
		
		case FASTTRAP_T_NOP:
			new_pc = pc + tp->ftt_size;
			break;

		case FASTTRAP_T_JMP:
		case FASTTRAP_T_CALL:
			if (tp->ftt_code == 0) {
				new_pc = tp->ftt_dest;
			} else {
				user_addr_t /* value ,*/ addr = tp->ftt_dest;

				if (tp->ftt_base != FASTTRAP_NOREG)
					addr += fasttrap_getreg(regs, tp->ftt_base);
				if (tp->ftt_index != FASTTRAP_NOREG)
					addr += fasttrap_getreg(regs, tp->ftt_index) <<
						tp->ftt_scale;
				
				if (tp->ftt_code == 1) {
					/*
					 * If there's a segment prefix for this
					 * instruction, we'll need to check permissions
					 * and bounds on the given selector, and adjust
					 * the address accordingly.
					 */
					if (tp->ftt_segment != FASTTRAP_SEG_NONE &&
					    fasttrap_do_seg(tp, regs, &addr) != 0) {
						fasttrap_sigsegv(p, uthread, addr);
						new_pc = pc;
						break;
					}
					
					uint32_t value32;
					addr = (user_addr_t)(uint32_t)addr;
					if (fasttrap_fuword32(addr, &value32) == -1) {
						fasttrap_sigsegv(p, uthread, addr);
						new_pc = pc;
						break;
					}
					new_pc = value32;
				} else {
					new_pc = addr;
				}
			}

			/*
			 * If this is a call instruction, we need to push the return
			 * address onto the stack. If this fails, we send the process
			 * a SIGSEGV and reset the pc to emulate what would happen if
			 * this instruction weren't traced.
			 */
			if (tp->ftt_type == FASTTRAP_T_CALL) {
				user_addr_t addr = regs32->uesp - sizeof (uint32_t);
				int ret = fasttrap_suword32(addr, (uint32_t)(pc + tp->ftt_size));
				
				if (ret == -1) {
					fasttrap_sigsegv(p, uthread, addr);
					new_pc = pc;
					break;
				}
				
				regs32->uesp = addr;
			}
			break;

		case FASTTRAP_T_COMMON:
		{
			user_addr_t addr, write_addr;
			uint8_t scratch[2 * FASTTRAP_MAX_INSTR_SIZE + 7];
			uint_t i = 0;

			/*
			 * Generic Instruction Tracing
			 * ---------------------------
			 *
			 * This is the layout of the scratch space in the user-land
			 * thread structure for our generated instructions.
			 *
			 *	32-bit mode			bytes
			 *	------------------------	-----
			 * a:	<original instruction>		<= 15
			 *	jmp	<pc + tp->ftt_size>	    5
			 * b:	<original instrction>		<= 15
			 *	int	T_DTRACE_RET		    2
			 *					-----
			 *					<= 37
			 *
			 *	64-bit mode			bytes
			 *	------------------------	-----
			 * a:	<original instruction>		<= 15
			 *	jmp	0(%rip)			    6
			 *	<pc + tp->ftt_size>		    8
			 * b:	<original instruction>		<= 15
			 * 	int	T_DTRACE_RET		    2
			 * 					-----
			 * 					<= 46
			 *
			 * The %pc is set to a, and curthread->t_dtrace_astpc is set
			 * to b. If we encounter a signal on the way out of the
			 * kernel, trap() will set %pc to curthread->t_dtrace_astpc
			 * so that we execute the original instruction and re-enter
			 * the kernel rather than redirecting to the next instruction.
			 *
			 * If there are return probes (so we know that we're going to
			 * need to reenter the kernel after executing the original
			 * instruction), the scratch space will just contain the
			 * original instruction followed by an interrupt -- the same
			 * data as at b.
			 */

			addr = uthread->t_dtrace_scratch->addr;
			write_addr = uthread->t_dtrace_scratch->write_addr;

			if (addr == 0LL || write_addr == 0LL) {
				fasttrap_sigtrap(p, uthread, pc); // Should be killing target proc
				new_pc = pc;
				break;
			}

			ASSERT(tp->ftt_size < FASTTRAP_MAX_INSTR_SIZE);

			uthread->t_dtrace_scrpc = addr;
			bcopy(tp->ftt_instr, &scratch[i], tp->ftt_size);
			i += tp->ftt_size;

			/*
			 * Set up the jmp to the next instruction; note that
			 * the size of the traced instruction cancels out.
			 */
			scratch[i++] = FASTTRAP_JMP32;
			/* LINTED - alignment */
			*(uint32_t *)&scratch[i] = pc - addr - 5;
			i += sizeof (uint32_t);

			uthread->t_dtrace_astpc = addr + i;
			bcopy(tp->ftt_instr, &scratch[i], tp->ftt_size);
			i += tp->ftt_size;
			scratch[i++] = FASTTRAP_INT;
			scratch[i++] = T_DTRACE_RET;
			
			ASSERT(i <= sizeof (scratch));

			if (fasttrap_copyout(scratch, write_addr, i)) {
				fasttrap_sigtrap(p, uthread, pc);
				new_pc = pc;
				break;
			}
			
			if (tp->ftt_retids != NULL) {
				uthread->t_dtrace_step = 1;
				uthread->t_dtrace_ret = 1;
				new_pc = uthread->t_dtrace_astpc;
			} else {
				new_pc = uthread->t_dtrace_scrpc;
			}
			
			uthread->t_dtrace_pc = pc;
			uthread->t_dtrace_npc = pc + tp->ftt_size;
			uthread->t_dtrace_on = 1;
			break;
		}
		
		default:
			panic("fasttrap: mishandled an instruction");
	}
	
done:
	/*
	 * APPLE NOTE:
	 *
	 * We're setting this earlier than Solaris does, to get a "correct"
	 * ustack() output. In the Sun code,  a() -> b() -> c() -> d() is
	 * reported at: d, b, a. The new way gives c, b, a, which is closer
	 * to correct, as the return instruction has already exectued.
	 */
	regs32->eip = new_pc;

	/*
	 * If there were no return probes when we first found the tracepoint,
	 * we should feel no obligation to honor any return probes that were
	 * subsequently enabled -- they'll just have to wait until the next
	 * time around.
	 */
	if (tp->ftt_retids != NULL) {
		/*
		 * We need to wait until the results of the instruction are
		 * apparent before invoking any return probes. If this
		 * instruction was emulated we can just call
		 * fasttrap_return_common(); if it needs to be executed, we
		 * need to wait until the user thread returns to the kernel.
		 */
		if (tp->ftt_type != FASTTRAP_T_COMMON) {
			fasttrap_return_common(regs, pc, pid, new_pc);
		} else {
			ASSERT(uthread->t_dtrace_ret != 0);
			ASSERT(uthread->t_dtrace_pc == pc);
			ASSERT(uthread->t_dtrace_scrpc != 0);
			ASSERT(new_pc == uthread->t_dtrace_astpc);
		}
	}

	return (0);
}