#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_saved_state_t ;
struct TYPE_16__ {int trapno; scalar_t__ rip; scalar_t__ err; void* cpu; } ;
struct TYPE_18__ {TYPE_1__ isf; scalar_t__ cr2; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
struct TYPE_19__ {int trapno; int err; scalar_t__ eip; scalar_t__ cr2; void* cpu; } ;
typedef  TYPE_4__ x86_saved_state32_t ;
struct TYPE_20__ {unsigned long dr6; } ;
typedef  TYPE_5__ x86_debug_state64_t ;
typedef  TYPE_5__ x86_debug_state32_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int user_addr_t ;
typedef  void* uint32_t ;
typedef  TYPE_7__* thread_t ;
typedef  TYPE_8__* pcb_t ;
typedef  int mach_exception_subcode_t ;
typedef  scalar_t__ mach_exception_code_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_22__ {TYPE_5__* ids; } ;
struct TYPE_17__ {scalar_t__ ids; } ;
struct TYPE_21__ {int /*<<< orphan*/  map; TYPE_2__ machine; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_UTRAP_x86 ; 
 int /*<<< orphan*/  DEBUG_KPRINT_SYSCALL_MASK (int,char*,int,int /*<<< orphan*/ ,int,void*,void*) ; 
 int EXC_ARITHMETIC ; 
 int EXC_BAD_ACCESS ; 
 int EXC_BAD_INSTRUCTION ; 
 int EXC_BREAKPOINT ; 
 scalar_t__ EXC_I386_BOUND ; 
 scalar_t__ EXC_I386_BPT ; 
 scalar_t__ EXC_I386_DIV ; 
 scalar_t__ EXC_I386_GPFLT ; 
 scalar_t__ EXC_I386_INTO ; 
 scalar_t__ EXC_I386_INVOP ; 
 scalar_t__ EXC_I386_INVTSSFLT ; 
 scalar_t__ EXC_I386_SEGNPFLT ; 
 scalar_t__ EXC_I386_SGL ; 
 scalar_t__ EXC_I386_STKFLT ; 
 int EXC_SOFTWARE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ABORTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THREAD_ABORTSAFE ; 
 TYPE_8__* THREAD_TO_PCB (TYPE_7__*) ; 
#define  T_DEBUG 143 
#define  T_DIVIDE_ERROR 142 
#define  T_DTRACE_RET 141 
#define  T_FLOATING_POINT_ERROR 140 
#define  T_FPU_FAULT 139 
#define  T_GENERAL_PROTECTION 138 
#define  T_INT3 137 
#define  T_INVALID_OPCODE 136 
#define  T_INVALID_TSS 135 
#define  T_NO_FPU 134 
#define  T_OUT_OF_BOUNDS 133 
#define  T_OVERFLOW 132 
#define  T_PAGE_FAULT 131 
 int T_PF_EXECUTE ; 
 int T_PF_WRITE ; 
#define  T_SEGMENT_NOT_PRESENT 130 
#define  T_SSE_FLOAT_ERROR 129 
#define  T_STACK_FAULT 128 
 int /*<<< orphan*/  VM_KERN_MEMORY_NONE ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int /*<<< orphan*/  __improbable (int) ; 
 int /*<<< orphan*/  __probable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* cpu_number () ; 
 TYPE_7__* current_thread () ; 
 int /*<<< orphan*/  dtrace_user_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpSSEexterrflt () ; 
 int /*<<< orphan*/  fpUDflt (int) ; 
 int /*<<< orphan*/  fpexterrflt () ; 
 int /*<<< orphan*/  fpextovrflt () ; 
 int /*<<< orphan*/  fpnoextflt () ; 
 int /*<<< orphan*/  fsigcs ; 
 int /*<<< orphan*/  fsigns ; 
 void** fsigs ; 
 int /*<<< orphan*/  i386_exception (int,scalar_t__,int) ; 
 scalar_t__ is_saved_state32 (int /*<<< orphan*/ *) ; 
 scalar_t__ is_saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pal_sti () ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 TYPE_4__* saved_state32 (int /*<<< orphan*/ *) ; 
 TYPE_3__* saved_state64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exception_return () ; 
 void* thread_fpsimd_hash (TYPE_7__*) ; 
 scalar_t__ thread_is_64bit_addr (TYPE_7__*) ; 
 int /*<<< orphan*/ * trap_type ; 
 int /*<<< orphan*/  user_page_fault_continue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_fault (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
user_trap(
	x86_saved_state_t *saved_state)
{
	int			exc;
	int			err;
	mach_exception_code_t 	code;
	mach_exception_subcode_t subcode;
	int			type;
	user_addr_t		vaddr;
	vm_prot_t		prot;
	thread_t		thread = current_thread();
	kern_return_t		kret;
	user_addr_t		rip;
	unsigned long 		dr6 = 0; /* 32 bit for i386, 64 bit for x86_64 */

	assert((is_saved_state32(saved_state) && !thread_is_64bit_addr(thread)) ||
	       (is_saved_state64(saved_state) &&  thread_is_64bit_addr(thread)));

	if (is_saved_state64(saved_state)) {
	        x86_saved_state64_t	*regs;

		regs = saved_state64(saved_state);

		/* Record cpu where state was captured */
		regs->isf.cpu = cpu_number();

		type = regs->isf.trapno;
		err  = (int)regs->isf.err & 0xffff;
		vaddr = (user_addr_t)regs->cr2;
		rip   = (user_addr_t)regs->isf.rip;
	} else {
		x86_saved_state32_t	*regs;

		regs = saved_state32(saved_state);

		/* Record cpu where state was captured */
		regs->cpu = cpu_number();

		type  = regs->trapno;
		err   = regs->err & 0xffff;
		vaddr = (user_addr_t)regs->cr2;
		rip   = (user_addr_t)regs->eip;
	}

	if ((type == T_DEBUG) && thread->machine.ids) {
		unsigned long clear = 0;
		/* Stash and clear this processor's DR6 value, in the event
		 * this was a debug register match
		 */
		__asm__ volatile ("mov %%db6, %0" : "=r" (dr6)); 
		__asm__ volatile ("mov %0, %%db6" : : "r" (clear));
	}

	pal_sti();

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
		(MACHDBG_CODE(DBG_MACH_EXCP_UTRAP_x86, type)) | DBG_FUNC_NONE,
		(unsigned)(vaddr>>32), (unsigned)vaddr,
		(unsigned)(rip>>32), (unsigned)rip, 0);

	code = 0;
	subcode = 0;
	exc = 0;

#if CONFIG_DTRACE
	/*
	 * DTrace does not consume all user traps, only INT_3's for now.
	 * Avoid needlessly calling tempDTraceTrapHook here, and let the
	 * INT_3 case handle them.
	 */
#endif
	
	DEBUG_KPRINT_SYSCALL_MASK(1,
		"user_trap: type=0x%x(%s) err=0x%x cr2=%p rip=%p\n",
		type, trap_type[type], err, (void *)(long) vaddr, (void *)(long) rip);
	
	switch (type) {

	    case T_DIVIDE_ERROR:
		exc = EXC_ARITHMETIC;
		code = EXC_I386_DIV;
		break;

	    case T_DEBUG:
		{
			pcb_t	pcb;
			/*
			 * Update the PCB with this processor's DR6 value
			 * in the event this was a debug register match.
			 */
			pcb = THREAD_TO_PCB(thread);
			if (pcb->ids) {
				/*
				 * We can get and set the status register
				 * in 32-bit mode even on a 64-bit thread
				 * because the high order bits are not
				 * used on x86_64
				 */
				if (thread_is_64bit_addr(thread)) {
					x86_debug_state64_t *ids = pcb->ids;
					ids->dr6 = dr6;
				} else { /* 32 bit thread */
					x86_debug_state32_t *ids = pcb->ids;
					ids->dr6 = (uint32_t) dr6;
				}
			}
			exc = EXC_BREAKPOINT;
			code = EXC_I386_SGL;
			break;
		}
	    case T_INT3:
#if CONFIG_DTRACE
		if (dtrace_user_probe(saved_state) == KERN_SUCCESS)
			return; /* If it succeeds, we are done... */
#endif
		exc = EXC_BREAKPOINT;
		code = EXC_I386_BPT;
		break;

	    case T_OVERFLOW:
		exc = EXC_ARITHMETIC;
		code = EXC_I386_INTO;
		break;

	    case T_OUT_OF_BOUNDS:
		exc = EXC_SOFTWARE;
		code = EXC_I386_BOUND;
		break;

	    case T_INVALID_OPCODE:
#if !defined(RC_HIDE_XNU_J137)
		fpUDflt(rip);	/* May return from exception directly */
#endif
		exc = EXC_BAD_INSTRUCTION;
		code = EXC_I386_INVOP;
		break;

	    case T_NO_FPU:
		fpnoextflt();
		return;

	    case T_FPU_FAULT:
		fpextovrflt(); /* Propagates exception directly, doesn't return */
		return;

	    case T_INVALID_TSS:	/* invalid TSS == iret with NT flag set */
		exc = EXC_BAD_INSTRUCTION;
		code = EXC_I386_INVTSSFLT;
		subcode = err;
		break;

	    case T_SEGMENT_NOT_PRESENT:
		exc = EXC_BAD_INSTRUCTION;
		code = EXC_I386_SEGNPFLT;
		subcode = err;
		break;

	    case T_STACK_FAULT:
		exc = EXC_BAD_INSTRUCTION;
		code = EXC_I386_STKFLT;
		subcode = err;
		break;

	    case T_GENERAL_PROTECTION:
		/*
		 * There's a wide range of circumstances which generate this
		 * class of exception. From user-space, many involve bad
		 * addresses (such as a non-canonical 64-bit address).
		 * So we map this to EXC_BAD_ACCESS (and thereby SIGSEGV).
		 * The trouble is cr2 doesn't contain the faulting address;
		 * we'd need to decode the faulting instruction to really
		 * determine this. We'll leave that to debuggers.
		 * However, attempted execution of privileged instructions
		 * (e.g. cli) also generate GP faults and so we map these to
		 * to EXC_BAD_ACCESS (and thence SIGSEGV) also - rather than
		 * EXC_BAD_INSTRUCTION which is more accurate. We just can't
		 * win!
		 */ 
		exc = EXC_BAD_ACCESS;
		code = EXC_I386_GPFLT;
		subcode = err;
		break;

	    case T_PAGE_FAULT:
	    {
		    prot = VM_PROT_READ;

		if (err & T_PF_WRITE)
		        prot |= VM_PROT_WRITE;
		if (__improbable(err & T_PF_EXECUTE))
		        prot |= VM_PROT_EXECUTE;
#if DEVELOPMENT || DEBUG
		uint32_t fsig = 0;
		fsig = thread_fpsimd_hash(thread);
#if DEBUG
		fsigs[0] = fsig;
#endif
#endif
		kret = vm_fault(thread->map,
				vaddr,
				prot, FALSE, VM_KERN_MEMORY_NONE,
				THREAD_ABORTSAFE, NULL, 0);
#if DEVELOPMENT || DEBUG
		if (fsig) {
			uint32_t fsig2 = thread_fpsimd_hash(thread);
#if DEBUG
			fsigcs++;
			fsigs[1] = fsig2;
#endif
			if (fsig != fsig2) {
				panic("FP/SIMD state hash mismatch across fault thread: %p 0x%x->0x%x", thread, fsig, fsig2);
			}
		} else {
#if DEBUG
			fsigns++;
#endif
		}
#endif
		if (__probable((kret == KERN_SUCCESS) || (kret == KERN_ABORTED))) {
			thread_exception_return();
			/*NOTREACHED*/
		}

	        user_page_fault_continue(kret);
	    }	/* NOTREACHED */
		break;

	    case T_SSE_FLOAT_ERROR:
		fpSSEexterrflt(); /* Propagates exception directly, doesn't return */
		return;


	    case T_FLOATING_POINT_ERROR:
		fpexterrflt(); /* Propagates exception directly, doesn't return */
		return;

	    case T_DTRACE_RET:
#if CONFIG_DTRACE
		if (dtrace_user_probe(saved_state) == KERN_SUCCESS)
			return; /* If it succeeds, we are done... */
#endif
		/*
		 * If we get an INT 0x7f when we do not expect to,
		 * treat it as an illegal instruction
		 */
		exc = EXC_BAD_INSTRUCTION;
		code = EXC_I386_INVOP;
		break;

	    default:
		panic("Unexpected user trap, type %d", type);
		return;
	}
	/* Note: Codepaths that directly return from user_trap() have pending
	 * ASTs processed in locore
	 */
	i386_exception(exc, code, subcode);
	/* NOTREACHED */
}