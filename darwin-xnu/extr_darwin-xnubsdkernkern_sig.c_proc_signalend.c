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
struct TYPE_5__ {scalar_t__ p_sigwaitcnt; int /*<<< orphan*/ * p_signalholder; int /*<<< orphan*/  p_sigmask; int /*<<< orphan*/  p_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_LINSIGNAL ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
proc_signalend(proc_t p, int locked)
{
	if (!locked)
		proc_lock(p);
	p->p_lflag &= ~P_LINSIGNAL;

	if (p->p_sigwaitcnt > 0)
		wakeup(&p->p_sigmask);

	p->p_signalholder = NULL;
	if (!locked)
		proc_unlock(p);
}