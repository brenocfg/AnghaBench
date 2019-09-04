#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {scalar_t__ p_signalholder; int p_lflag; int /*<<< orphan*/  p_sigwaitcnt; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  p_sigmask; } ;

/* Variables and functions */
 int P_LINSIGNAL ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

void
proc_signalstart(proc_t p, int locked)
{
	if (!locked)
		proc_lock(p);
	
	if(p->p_signalholder == current_thread())
		panic("proc_signalstart: thread attempting to signal a process for which it holds the signal lock");	
	
	p->p_sigwaitcnt++;
	while ((p->p_lflag & P_LINSIGNAL) == P_LINSIGNAL)
		msleep(&p->p_sigmask, &p->p_mlock, 0, "proc_signstart", NULL);
	p->p_sigwaitcnt--;

	p->p_lflag |= P_LINSIGNAL;
	p->p_signalholder = current_thread();
	if (!locked)
		proc_unlock(p);
}