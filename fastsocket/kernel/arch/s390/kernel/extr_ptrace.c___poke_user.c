#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fpc; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct TYPE_8__ {int /*<<< orphan*/  per_info; TYPE_2__ fp_regs; int /*<<< orphan*/  orig_gpr2; int /*<<< orphan*/ * acrs; TYPE_1__ psw; } ;
struct user {TYPE_3__ regs; } ;
struct TYPE_9__ {unsigned int* acrs; int /*<<< orphan*/  per_info; int /*<<< orphan*/  fp_regs; } ;
struct task_struct {TYPE_4__ thread; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_10__ {scalar_t__ orig_gpr2; int /*<<< orphan*/  psw; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int EINVAL ; 
 scalar_t__ FPC_VALID_MASK ; 
 int /*<<< orphan*/  FixPerRegisters (struct task_struct*) ; 
 scalar_t__ PSW_ADDR_AMODE ; 
 scalar_t__ PSW_MASK_MERGE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  psw_user32_bits ; 
 int /*<<< orphan*/  psw_user_bits ; 
 TYPE_5__* task_pt_regs (struct task_struct*) ; 

__attribute__((used)) static int __poke_user(struct task_struct *child, addr_t addr, addr_t data)
{
	struct user *dummy = NULL;
	addr_t offset;

	if (addr < (addr_t) &dummy->regs.acrs) {
		/*
		 * psw and gprs are stored on the stack
		 */
		if (addr == (addr_t) &dummy->regs.psw.mask &&
#ifdef CONFIG_COMPAT
		    data != PSW_MASK_MERGE(psw_user32_bits, data) &&
#endif
		    data != PSW_MASK_MERGE(psw_user_bits, data))
			/* Invalid psw mask. */
			return -EINVAL;
#ifndef CONFIG_64BIT
		if (addr == (addr_t) &dummy->regs.psw.addr)
			/* I'd like to reject addresses without the
			   high order bit but older gdb's rely on it */
			data |= PSW_ADDR_AMODE;
#endif
		*(addr_t *)((addr_t) &task_pt_regs(child)->psw + addr) = data;

	} else if (addr < (addr_t) (&dummy->regs.orig_gpr2)) {
		/*
		 * access registers are stored in the thread structure
		 */
		offset = addr - (addr_t) &dummy->regs.acrs;
#ifdef CONFIG_64BIT
		/*
		 * Very special case: old & broken 64 bit gdb writing
		 * to acrs[15] with a 64 bit value. Ignore the lower
		 * half of the value and write the upper 32 bit to
		 * acrs[15]. Sick...
		 */
		if (addr == (addr_t) &dummy->regs.acrs[15])
			child->thread.acrs[15] = (unsigned int) (data >> 32);
		else
#endif
		*(addr_t *)((addr_t) &child->thread.acrs + offset) = data;

	} else if (addr == (addr_t) &dummy->regs.orig_gpr2) {
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		task_pt_regs(child)->orig_gpr2 = data;

	} else if (addr < (addr_t) &dummy->regs.fp_regs) {
		/*
		 * prevent writes of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		return 0;

	} else if (addr < (addr_t) (&dummy->regs.fp_regs + 1)) {
		/*
		 * floating point regs. are stored in the thread structure
		 */
		if (addr == (addr_t) &dummy->regs.fp_regs.fpc &&
		    (data & ~((unsigned long) FPC_VALID_MASK
			      << (BITS_PER_LONG - 32))) != 0)
			return -EINVAL;
		offset = addr - (addr_t) &dummy->regs.fp_regs;
		*(addr_t *)((addr_t) &child->thread.fp_regs + offset) = data;

	} else if (addr < (addr_t) (&dummy->regs.per_info + 1)) {
		/*
		 * per_info is found in the thread structure 
		 */
		offset = addr - (addr_t) &dummy->regs.per_info;
		*(addr_t *)((addr_t) &child->thread.per_info + offset) = data;

	}

	FixPerRegisters(child);
	return 0;
}