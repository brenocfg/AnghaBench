#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rsp; } ;
struct TYPE_7__ {scalar_t__ rdi; uintptr_t rsi; int /*<<< orphan*/  r8; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rdx; TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {scalar_t__ fbtp_roffset; int fbtp_rval; int /*<<< orphan*/  fbtp_id; scalar_t__ fbtp_patchpoint; struct TYPE_8__* fbtp_hashnext; } ;
typedef  TYPE_3__ fbt_probe_t ;
struct TYPE_9__ {uintptr_t cpu_dtrace_caller; } ;

/* Variables and functions */
 TYPE_5__* CPU ; 
 size_t FBT_ADDR2NDX (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,scalar_t__,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** fbt_probetab ; 

int
fbt_invop(uintptr_t addr, uintptr_t *state, uintptr_t rval)
{
	fbt_probe_t *fbt = fbt_probetab[FBT_ADDR2NDX(addr)];

	for (; fbt != NULL; fbt = fbt->fbtp_hashnext) {
		if ((uintptr_t)fbt->fbtp_patchpoint == addr) {

			if (fbt->fbtp_roffset == 0) {
				x86_saved_state64_t *regs = (x86_saved_state64_t *)state;

				CPU->cpu_dtrace_caller = *(uintptr_t *)(((uintptr_t)(regs->isf.rsp))+sizeof(uint64_t)); // 8(%rsp)
				/* 64-bit ABI, arguments passed in registers. */
				dtrace_probe(fbt->fbtp_id, regs->rdi, regs->rsi, regs->rdx, regs->rcx, regs->r8);
				CPU->cpu_dtrace_caller = 0;
			} else {

				dtrace_probe(fbt->fbtp_id, fbt->fbtp_roffset, rval, 0, 0, 0);
				CPU->cpu_dtrace_caller = 0;
			}

			return (fbt->fbtp_rval);
		}
	}

	return (0);
}