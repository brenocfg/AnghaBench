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
struct arm_saved_state {int cpsr; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_INTR ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PSR_MODE_MASK ; 
 int PSR_USER_MODE ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (int /*<<< orphan*/ ) ; 

void
interrupt_trace(
		struct arm_saved_state * regs)
{
#define	UMODE(rp)	(((rp)->cpsr & PSR_MODE_MASK) == PSR_USER_MODE)

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		MACHDBG_CODE(DBG_MACH_EXCP_INTR, 0) | DBG_FUNC_START,
		0, UMODE(regs) ? regs->pc : VM_KERNEL_UNSLIDE(regs->pc),
		UMODE(regs), 0, 0);
}