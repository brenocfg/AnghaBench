#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ps; unsigned long windowstart; scalar_t__ a; int /*<<< orphan*/  sar; int /*<<< orphan*/  lcount; int /*<<< orphan*/  lend; int /*<<< orphan*/  lbeg; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ xtensa_gregset_t ;
struct pt_regs {unsigned long windowbase; unsigned long windowstart; unsigned long wmask; int ps; scalar_t__ areg; int /*<<< orphan*/  sar; int /*<<< orphan*/  lcount; int /*<<< orphan*/  lend; int /*<<< orphan*/  lbeg; int /*<<< orphan*/  pc; } ;
typedef  int /*<<< orphan*/  elfregs ;

/* Variables and functions */
 int PS_EXCM_BIT ; 
 unsigned long WSBITS ; 
 unsigned long XCHAL_NUM_AREGS ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void xtensa_elf_core_copy_regs (xtensa_gregset_t *elfregs, struct pt_regs *regs)
{
	unsigned long wb, ws, wm;
	int live, last;

	wb = regs->windowbase;
	ws = regs->windowstart;
	wm = regs->wmask;
	ws = ((ws >> wb) | (ws << (WSBITS - wb))) & ((1 << WSBITS) - 1);

	/* Don't leak any random bits. */

	memset(elfregs, 0, sizeof (elfregs));

	/* Note:  PS.EXCM is not set while user task is running; its
	 * being set in regs->ps is for exception handling convenience.
	 */

	elfregs->pc		= regs->pc;
	elfregs->ps		= (regs->ps & ~(1 << PS_EXCM_BIT));
	elfregs->lbeg		= regs->lbeg;
	elfregs->lend		= regs->lend;
	elfregs->lcount		= regs->lcount;
	elfregs->sar		= regs->sar;
	elfregs->windowstart	= ws;

	live = (wm & 2) ? 4 : (wm & 4) ? 8 : (wm & 8) ? 12 : 16;
	last = XCHAL_NUM_AREGS - (wm >> 4) * 4;
	memcpy(elfregs->a, regs->areg, live * 4);
	memcpy(elfregs->a + last, regs->areg + last, (wm >> 4) * 16);
}