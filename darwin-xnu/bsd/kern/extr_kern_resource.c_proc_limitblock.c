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
struct TYPE_5__ {int p_lflag; int /*<<< orphan*/  p_mlock; int /*<<< orphan*/  p_olimit; } ;

/* Variables and functions */
 int P_LLIMCHANGE ; 
 int P_LLIMWAIT ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 

void
proc_limitblock(proc_t p)
{
	proc_lock(p);
	while (p->p_lflag & P_LLIMCHANGE) {
		p->p_lflag |= P_LLIMWAIT;
		msleep(&p->p_olimit, &p->p_mlock, 0, "proc_limitblock", NULL);
	}
	p->p_lflag |= P_LLIMCHANGE;
	proc_unlock(p);

}