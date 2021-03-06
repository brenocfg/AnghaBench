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
struct TYPE_5__ {int p_lflag; int /*<<< orphan*/ * p_transholder; } ;

/* Variables and functions */
 int P_LINTRANSIT ; 
 int P_LTRANSCOMMIT ; 
 int P_LTRANSWAIT ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
proc_transend(proc_t p, int locked)
{
	if (locked == 0)
		proc_lock(p);

	p->p_lflag &= ~( P_LINTRANSIT | P_LTRANSCOMMIT);
	p->p_transholder = NULL;

	if ((p->p_lflag & P_LTRANSWAIT) == P_LTRANSWAIT) {
		p->p_lflag &= ~P_LTRANSWAIT;
		wakeup(&p->p_lflag);
	}
	if (locked == 0)
		proc_unlock(p);
}