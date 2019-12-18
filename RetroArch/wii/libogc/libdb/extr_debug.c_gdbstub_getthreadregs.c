#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
struct TYPE_6__ {int /*<<< orphan*/  FPSCR; int /*<<< orphan*/  XER; int /*<<< orphan*/  CTR; int /*<<< orphan*/  LR; int /*<<< orphan*/  CR; int /*<<< orphan*/  MSR; int /*<<< orphan*/  FPR; int /*<<< orphan*/  GPR; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
typedef  TYPE_2__ lwp_cntrl ;
struct TYPE_8__ {int /*<<< orphan*/  FPSCR; int /*<<< orphan*/  XER; int /*<<< orphan*/  CTR; int /*<<< orphan*/  LR; int /*<<< orphan*/  CR; int /*<<< orphan*/  SRR1; int /*<<< orphan*/  SRR0; int /*<<< orphan*/  FPR; int /*<<< orphan*/  GPR; } ;
typedef  TYPE_3__ frame_context ;

/* Variables and functions */
 TYPE_2__* gdbstub_indextoid (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 gdbstub_getthreadregs(s32 thread,frame_context *frame)
{
	lwp_cntrl *th;

	th = gdbstub_indextoid(thread);
	if(th) {
		memcpy(frame->GPR,th->context.GPR,(32*4));
		memcpy(frame->FPR,th->context.FPR,(32*8));
		frame->SRR0 = th->context.LR;
		frame->SRR1 = th->context.MSR;
		frame->CR = th->context.CR;
		frame->LR = th->context.LR;
		frame->CTR = th->context.CTR;
		frame->XER = th->context.XER;
		frame->FPSCR = th->context.FPSCR;
		return 1;
	}
	return 0;
}