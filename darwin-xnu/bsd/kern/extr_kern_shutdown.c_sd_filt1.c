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
struct sd_filterargs {int delayterm; int shutdownstate; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {int p_flag; scalar_t__ p_ppid; scalar_t__ p_stat; int p_shutdownstate; int p_lflag; int p_sigcatch; } ;

/* Variables and functions */
 int P_LDELAYTERM ; 
 int P_SYSTEM ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SZOMB ; 
 TYPE_1__* current_proc () ; 
 int sigmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sd_filt1(proc_t p, void * args)
{
	proc_t self = current_proc();
	struct sd_filterargs * sf = (struct sd_filterargs *)args;
	int delayterm = sf-> delayterm;
	int shutdownstate = sf->shutdownstate;

	if (((p->p_flag&P_SYSTEM) != 0) || (p->p_ppid == 0) 
		||(p == self) || (p->p_stat == SZOMB) 
		|| (p->p_shutdownstate != shutdownstate) 
		||((delayterm == 0) && ((p->p_lflag& P_LDELAYTERM) == P_LDELAYTERM))
		|| ((p->p_sigcatch & sigmask(SIGTERM))== 0)) {
			return(0);
		}
        else 
                return(1);
}