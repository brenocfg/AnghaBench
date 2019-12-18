#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rflags; scalar_t__ err; int /*<<< orphan*/  rip; } ;
struct TYPE_8__ {TYPE_1__ isf; int /*<<< orphan*/  cr2; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  unsigned int kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {TYPE_2__* cpu_fatal_trap_state; TYPE_2__* cpu_post_fatal_trap_state; } ;
struct TYPE_9__ {int /*<<< orphan*/  is_conn; } ;

/* Variables and functions */
 int EFL_TF ; 
 unsigned int EXC_ARITHMETIC ; 
 unsigned int EXC_BAD_ACCESS ; 
 unsigned int EXC_BAD_INSTRUCTION ; 
 unsigned int EXC_BREAKPOINT ; 
 unsigned int EXC_I386_ALIGNFLT ; 
 unsigned int EXC_I386_BOUNDFLT ; 
 unsigned int EXC_I386_BPTFLT ; 
 unsigned int EXC_I386_DIVERR ; 
 unsigned int EXC_I386_GPFLT ; 
 unsigned int EXC_I386_INTOFLT ; 
 unsigned int EXC_I386_INVOPFLT ; 
 unsigned int EXC_I386_SEGNPFLT ; 
 unsigned int EXC_I386_STKFLT ; 
 unsigned int EXC_SOFTWARE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  T_DEBUG 138 
#define  T_DIVIDE_ERROR 137 
#define  T_GENERAL_PROTECTION 136 
#define  T_INT3 135 
#define  T_INVALID_OPCODE 134 
#define  T_OUT_OF_BOUNDS 133 
#define  T_OVERFLOW 132 
#define  T_PAGE_FAULT 131 
#define  T_SEGMENT_NOT_PRESENT 130 
#define  T_STACK_FAULT 129 
#define  T_WATCHPOINT 128 
 TYPE_6__* current_cpu_datap () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  enable_preemption_no_check () ; 
 int /*<<< orphan*/  handle_debugger_trap (unsigned int,unsigned int,unsigned int,TYPE_2__*) ; 
 TYPE_4__ kdp ; 
 int /*<<< orphan*/  kprintf (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 

boolean_t
kdp_i386_trap(
    unsigned int		trapno,
    x86_saved_state64_t	*saved_state,
    kern_return_t	result,
    vm_offset_t		va
)
{
    unsigned int exception, code, subcode = 0;
    boolean_t prev_interrupts_state;

    if (trapno != T_INT3 && trapno != T_DEBUG) {
    	kprintf("Debugger: Unexpected kernel trap number: "
		"0x%x, RIP: 0x%llx, CR2: 0x%llx\n",
		trapno, saved_state->isf.rip, saved_state->cr2);
	if (!kdp.is_conn)
	    return FALSE;
    }

    prev_interrupts_state = ml_set_interrupts_enabled(FALSE);
    disable_preemption();

    if (saved_state->isf.rflags & EFL_TF) {
	    enable_preemption_no_check();
    }

    switch (trapno) {
    
    case T_DIVIDE_ERROR:
	exception = EXC_ARITHMETIC;
	code = EXC_I386_DIVERR;
	break;
    
    case T_OVERFLOW:
	exception = EXC_SOFTWARE;
	code = EXC_I386_INTOFLT;
	break;
    
    case T_OUT_OF_BOUNDS:
	exception = EXC_ARITHMETIC;
	code = EXC_I386_BOUNDFLT;
	break;
    
    case T_INVALID_OPCODE:
	exception = EXC_BAD_INSTRUCTION;
	code = EXC_I386_INVOPFLT;
	break;
    
    case T_SEGMENT_NOT_PRESENT:
	exception = EXC_BAD_INSTRUCTION;
	code = EXC_I386_SEGNPFLT;
	subcode	= (unsigned int)saved_state->isf.err;
	break;
    
    case T_STACK_FAULT:
	exception = EXC_BAD_INSTRUCTION;
	code = EXC_I386_STKFLT;
	subcode	= (unsigned int)saved_state->isf.err;
	break;
    
    case T_GENERAL_PROTECTION:
	exception = EXC_BAD_INSTRUCTION;
	code = EXC_I386_GPFLT;
	subcode	= (unsigned int)saved_state->isf.err;
	break;
	
    case T_PAGE_FAULT:
    	exception = EXC_BAD_ACCESS;
	code = result;
	subcode = (unsigned int)va;
	break;
    
    case T_WATCHPOINT:
	exception = EXC_SOFTWARE;
	code = EXC_I386_ALIGNFLT;
	break;
	
    case T_DEBUG:
    case T_INT3:
	exception = EXC_BREAKPOINT;
	code = EXC_I386_BPTFLT;
	break;

    default:
    	exception = EXC_BAD_INSTRUCTION;
	code = trapno;
	break;
    }

    if (current_cpu_datap()->cpu_fatal_trap_state) {
	    current_cpu_datap()->cpu_post_fatal_trap_state = saved_state;
	    saved_state = current_cpu_datap()->cpu_fatal_trap_state;
    }

    handle_debugger_trap(exception, code, subcode, saved_state);

    enable_preemption();
    ml_set_interrupts_enabled(prev_interrupts_state);

    /* If the instruction single step bit is set, disable kernel preemption
     */
    if (saved_state->isf.rflags & EFL_TF) {
	    disable_preemption();
    }

    return TRUE;
}