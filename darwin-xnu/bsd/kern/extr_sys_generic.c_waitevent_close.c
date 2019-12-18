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
struct proc {int dummy; } ;
struct pipe {TYPE_2__ pipe_evlist; } ;
struct fileproc {scalar_t__ f_type; scalar_t__ f_data; int /*<<< orphan*/  f_flags; } ;
struct TYPE_3__ {struct eventqelt* tqe_next; } ;
struct eventqelt {struct proc* ee_proc; TYPE_1__ ee_slist; } ;

/* Variables and functions */
 scalar_t__ DTYPE_PIPE ; 
 scalar_t__ DTYPE_SOCKET ; 
 int EINVAL ; 
 int /*<<< orphan*/  EVPROCDEQUE (struct proc*,struct eventqelt*) ; 
 int /*<<< orphan*/  FP_WAITEVENT ; 
 int /*<<< orphan*/  FREE (struct eventqelt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_2__*,struct eventqelt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ee_slist ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

int
waitevent_close(struct proc *p, struct fileproc *fp)
{
	struct eventqelt *evq;


	fp->f_flags &= ~FP_WAITEVENT;

#if SOCKETS
	if (fp->f_type == DTYPE_SOCKET) {
	        socket_lock((struct socket *)fp->f_data, 1);
		evq = ((struct socket *)fp->f_data)->so_evlist.tqh_first;
	} else
#endif /* SOCKETS */
	if (fp->f_type == DTYPE_PIPE) {
	        PIPE_LOCK((struct pipe *)fp->f_data);
		evq = ((struct pipe *)fp->f_data)->pipe_evlist.tqh_first;
	}
	else {
		return(EINVAL);
	}
	proc_fdunlock(p);


	// locate event if possible
	for ( ; evq != NULL; evq = evq->ee_slist.tqe_next) {
	        if (evq->ee_proc == p)
		        break;
	}
	if (evq == NULL) {
#if SOCKETS
	        if (fp->f_type == DTYPE_SOCKET) 
		        socket_unlock((struct socket *)fp->f_data, 1);
		else 
#endif /* SOCKETS */
		        PIPE_UNLOCK((struct pipe *)fp->f_data);

		proc_fdlock(p);

		return(EINVAL);
	}
	EVPROCDEQUE(p, evq);

#if SOCKETS
	if (fp->f_type == DTYPE_SOCKET) {
		TAILQ_REMOVE(&((struct socket *)fp->f_data)->so_evlist, evq, ee_slist);
		socket_unlock((struct socket *)fp->f_data, 1);
	} else
#endif /* SOCKETS */
	{
		TAILQ_REMOVE(&((struct pipe *)fp->f_data)->pipe_evlist, evq, ee_slist);
		PIPE_UNLOCK((struct pipe *)fp->f_data);
	}
	FREE(evq, M_TEMP);

	proc_fdlock(p);

	return(0);
}