#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {long* gr; } ;

/* Variables and functions */
 long EIO ; 
#define  PTRACE_PEEKUSR 129 
#define  PTRACE_POKEUSR 128 
 long PT_FR0 ; 
 int /*<<< orphan*/  PT_FR31 ; 
 long PT_GR1 ; 
 long PT_GR31 ; 
 long PT_IAOQ0 ; 
 long PT_IAOQ1 ; 
 long PT_PSW ; 
 long PT_SAR ; 
 long USER_PSW_BITS ; 
 long ptrace_request (struct task_struct*,long,long,long) ; 
 long put_user (unsigned long,unsigned long*) ; 
 TYPE_1__* task_regs (struct task_struct*) ; 

long arch_ptrace(struct task_struct *child, long request, long addr, long data)
{
	unsigned long tmp;
	long ret = -EIO;

	switch (request) {

	/* Read the word at location addr in the USER area.  For ptraced
	   processes, the kernel saves all regs on a syscall. */
	case PTRACE_PEEKUSR:
		if ((addr & (sizeof(long)-1)) ||
		    (unsigned long) addr >= sizeof(struct pt_regs))
			break;
		tmp = *(unsigned long *) ((char *) task_regs(child) + addr);
		ret = put_user(tmp, (unsigned long *) data);
		break;

	/* Write the word at location addr in the USER area.  This will need
	   to change when the kernel no longer saves all regs on a syscall.
	   FIXME.  There is a problem at the moment in that r3-r18 are only
	   saved if the process is ptraced on syscall entry, and even then
	   those values are overwritten by actual register values on syscall
	   exit. */
	case PTRACE_POKEUSR:
		/* Some register values written here may be ignored in
		 * entry.S:syscall_restore_rfi; e.g. iaoq is written with
		 * r31/r31+4, and not with the values in pt_regs.
		 */
		if (addr == PT_PSW) {
			/* Allow writing to Nullify, Divide-step-correction,
			 * and carry/borrow bits.
			 * BEWARE, if you set N, and then single step, it won't
			 * stop on the nullified instruction.
			 */
			data &= USER_PSW_BITS;
			task_regs(child)->gr[0] &= ~USER_PSW_BITS;
			task_regs(child)->gr[0] |= data;
			ret = 0;
			break;
		}

		if ((addr & (sizeof(long)-1)) ||
		    (unsigned long) addr >= sizeof(struct pt_regs))
			break;
		if ((addr >= PT_GR1 && addr <= PT_GR31) ||
				addr == PT_IAOQ0 || addr == PT_IAOQ1 ||
				(addr >= PT_FR0 && addr <= PT_FR31 + 4) ||
				addr == PT_SAR) {
			*(unsigned long *) ((char *) task_regs(child) + addr) = data;
			ret = 0;
		}
		break;

	default:
		ret = ptrace_request(child, request, addr, data);
		break;
	}

	return ret;
}