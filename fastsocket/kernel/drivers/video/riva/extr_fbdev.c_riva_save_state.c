#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct riva_regs {int /*<<< orphan*/ * seq; int /*<<< orphan*/ * gra; int /*<<< orphan*/ * attr; int /*<<< orphan*/ * crtc; int /*<<< orphan*/  misc_output; int /*<<< orphan*/  ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* UnloadStateExt ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* LockUnlock ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct riva_par {TYPE_1__ riva; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTRin (struct riva_par*,int) ; 
 int /*<<< orphan*/  CRTCin (struct riva_par*,int) ; 
 int /*<<< orphan*/  GRAin (struct riva_par*,int) ; 
 int /*<<< orphan*/  MISCin (struct riva_par*) ; 
 int NUM_ATC_REGS ; 
 int NUM_CRT_REGS ; 
 int NUM_GRC_REGS ; 
 int NUM_SEQ_REGS ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  SEQin (struct riva_par*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void riva_save_state(struct riva_par *par, struct riva_regs *regs)
{
	int i;

	NVTRACE_ENTER();
	par->riva.LockUnlock(&par->riva, 0);

	par->riva.UnloadStateExt(&par->riva, &regs->ext);

	regs->misc_output = MISCin(par);

	for (i = 0; i < NUM_CRT_REGS; i++)
		regs->crtc[i] = CRTCin(par, i);

	for (i = 0; i < NUM_ATC_REGS; i++)
		regs->attr[i] = ATTRin(par, i);

	for (i = 0; i < NUM_GRC_REGS; i++)
		regs->gra[i] = GRAin(par, i);

	for (i = 0; i < NUM_SEQ_REGS; i++)
		regs->seq[i] = SEQin(par, i);
	NVTRACE_LEAVE();
}