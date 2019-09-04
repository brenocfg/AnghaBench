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
struct TYPE_4__ {struct eventqelt* tqh_first; } ;
struct socket {TYPE_2__ so_evlist; } ;
struct TYPE_3__ {struct eventqelt* tqe_next; } ;
struct eventqelt {int ee_flags; int /*<<< orphan*/  ee_proc; TYPE_1__ ee_slist; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVPROCDEQUE (int /*<<< orphan*/ ,struct eventqelt*) ; 
 int EV_QUEUED ; 
 int /*<<< orphan*/  FREE (struct eventqelt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_2__*,struct eventqelt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ee_slist ; 

void
evsofree(struct socket *sp)
{
        struct eventqelt *evq, *next;
	proc_t 	p;

	if (sp == NULL)
	        return;

	for (evq = sp->so_evlist.tqh_first; evq != NULL; evq = next) {
	        next = evq->ee_slist.tqe_next;
		p = evq->ee_proc;

		if (evq->ee_flags & EV_QUEUED) {
		        EVPROCDEQUE(p, evq);
		}
		TAILQ_REMOVE(&sp->so_evlist, evq, ee_slist); // remove from socket q
		FREE(evq, M_TEMP);
	}
}