#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/  xer; int /*<<< orphan*/  ctr; int /*<<< orphan*/  link; int /*<<< orphan*/  ccr; int /*<<< orphan*/  msr; int /*<<< orphan*/  nip; int /*<<< orphan*/ * gpr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * evr; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NUMREGBYTES ; 
 int /*<<< orphan*/  UNPACK32 (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  UNPACK64 (int /*<<< orphan*/ ,unsigned long*) ; 
 TYPE_2__* current ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	unsigned long *ptr = gdb_regs;
	int reg;

	for (reg = 0; reg < 32; reg++)
		UNPACK64(regs->gpr[reg], ptr);

#ifdef CONFIG_FSL_BOOKE
#ifdef CONFIG_SPE
	for (reg = 0; reg < 32; reg++)
		UNPACK64(current->thread.evr[reg], ptr);
#else
	ptr += 32;
#endif
#else
	/* fp registers not used by kernel, leave zero */
	ptr += 32 * 8 / sizeof(int);
#endif

	UNPACK64(regs->nip, ptr);
	UNPACK64(regs->msr, ptr);
	UNPACK32(regs->ccr, ptr);
	UNPACK64(regs->link, ptr);
	UNPACK64(regs->ctr, ptr);
	UNPACK32(regs->xer, ptr);

	BUG_ON((unsigned long)ptr >
	       (unsigned long)(((void *)gdb_regs) + NUMREGBYTES));
}