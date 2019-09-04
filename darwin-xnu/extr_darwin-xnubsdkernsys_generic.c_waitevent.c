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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct waitevent_args {scalar_t__ tv; int /*<<< orphan*/  u_req; } ;
struct user64_timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct user32_timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct eventreq64 {int /*<<< orphan*/  er_eventbits; scalar_t__ er_handle; int /*<<< orphan*/  er_wcnt; int /*<<< orphan*/  er_rcnt; int /*<<< orphan*/  er_ecnt; scalar_t__ er_data; int /*<<< orphan*/  er_type; } ;
struct eventreq32 {int /*<<< orphan*/  er_eventbits; int /*<<< orphan*/  er_wcnt; int /*<<< orphan*/  er_rcnt; int /*<<< orphan*/  er_ecnt; scalar_t__ er_data; scalar_t__ er_handle; int /*<<< orphan*/  er_type; } ;
struct eventqelt {struct eventreq64 ee_req; int /*<<< orphan*/  ee_flags; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  atv64 ;
typedef  int /*<<< orphan*/  atv32 ;
struct TYPE_9__ {struct eventqelt* tqh_first; } ;
struct TYPE_8__ {TYPE_5__ p_evlist; int /*<<< orphan*/  p_mlock; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_NONE ; 
 int DBG_FUNC_START ; 
 int DBG_MISC_WAIT ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int /*<<< orphan*/  EV_QUEUED ; 
 int EWOULDBLOCK ; 
 scalar_t__ FALSE ; 
 scalar_t__ IS_64BIT_PROCESS (TYPE_1__*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int PCATCH ; 
 int PSOCK ; 
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_5__*,struct eventqelt*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (scalar_t__,scalar_t__*) ; 
 int copyin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ee_plist ; 
 scalar_t__ itimerfix (struct timeval*) ; 
 int msleep1 (TYPE_5__*,int /*<<< orphan*/ *,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  proc_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_unlock (TYPE_1__*) ; 
 scalar_t__ tvtoabstime (struct timeval*) ; 

int
waitevent(proc_t p, struct waitevent_args *uap, int *retval)
{
        int error = 0;
	struct eventqelt *evq;
	struct eventreq64 *erp;
	uint64_t abstime, interval;
	boolean_t fast_poll = FALSE;
	union {
	        struct eventreq64 er64;
	        struct eventreq32 er32;
	} uer = {};

	interval = 0;

	if (uap->tv) {
		struct timeval atv;
		/*
		 * check for fast poll method
		 */
		if (IS_64BIT_PROCESS(p)) {
		        if (uap->tv == (user_addr_t)-1)
			        fast_poll = TRUE;
		} else if (uap->tv == (user_addr_t)((uint32_t)-1))
		        fast_poll = TRUE;

		if (fast_poll == TRUE) {
		        if (p->p_evlist.tqh_first == NULL) {
				KERNEL_DEBUG(DBG_MISC_WAIT|DBG_FUNC_NONE, -1,0,0,0,0);
				/*
				 * poll failed
				 */
			        *retval = 1;
				return (0);
			}
			proc_lock(p);
			goto retry;
		}
		if (IS_64BIT_PROCESS(p)) {
			struct user64_timeval atv64;
			error = copyin(uap->tv, (caddr_t)&atv64, sizeof(atv64));
			/* Loses resolution - assume timeout < 68 years */
			atv.tv_sec = atv64.tv_sec;
			atv.tv_usec = atv64.tv_usec;
		} else {
			struct user32_timeval atv32;
			error = copyin(uap->tv, (caddr_t)&atv32, sizeof(atv32));
			atv.tv_sec = atv32.tv_sec;
			atv.tv_usec = atv32.tv_usec;
		}

		if (error)
			return(error);
		if (itimerfix(&atv)) {
			error = EINVAL;
			return(error);
		}
		interval = tvtoabstime(&atv);
	}
	KERNEL_DEBUG(DBG_MISC_WAIT|DBG_FUNC_START, 0,0,0,0,0);

	proc_lock(p);
retry:
	if ((evq = p->p_evlist.tqh_first) != NULL) {
	        /*
		 * found one... make a local copy while it's still on the queue
		 * to prevent it from changing while in the midst of copying
		 * don't want to hold the proc lock across a copyout because
		 * it might block on a page fault at the target in user space
		 */
	        erp = &evq->ee_req;

		if (IS_64BIT_PROCESS(p))
		        bcopy((caddr_t)erp, (caddr_t)&uer.er64, sizeof (struct eventreq64));
		else {
		        uer.er32.er_type  = erp->er_type;
		        uer.er32.er_handle  = erp->er_handle;
		        uer.er32.er_data  = (uint32_t)erp->er_data;
		        uer.er32.er_ecnt  = erp->er_ecnt;
		        uer.er32.er_rcnt  = erp->er_rcnt;
		        uer.er32.er_wcnt  = erp->er_wcnt;
		        uer.er32.er_eventbits = erp->er_eventbits;
		}
	        TAILQ_REMOVE(&p->p_evlist, evq, ee_plist);

		evq->ee_flags &= ~EV_QUEUED;

		proc_unlock(p);

		if (IS_64BIT_PROCESS(p))
		        error = copyout((caddr_t)&uer.er64, uap->u_req, sizeof(struct eventreq64));
		else
		        error = copyout((caddr_t)&uer.er32, uap->u_req, sizeof(struct eventreq32));

		KERNEL_DEBUG(DBG_MISC_WAIT|DBG_FUNC_END, error,
			     evq->ee_req.er_handle,evq->ee_req.er_eventbits,(uint32_t)evq,0);
		return (error);
	}
	else {
		if (uap->tv && interval == 0) {
			proc_unlock(p);
			*retval = 1;  // poll failed

			KERNEL_DEBUG(DBG_MISC_WAIT|DBG_FUNC_END, error,0,0,0,0);
			return (error);
		}
		if (interval != 0)
			clock_absolutetime_interval_to_deadline(interval, &abstime);
		else
		        abstime = 0;

		KERNEL_DEBUG(DBG_MISC_WAIT, 1,(uint32_t)&p->p_evlist,0,0,0);

		error = msleep1(&p->p_evlist, &p->p_mlock, (PSOCK | PCATCH), "waitevent", abstime);

		KERNEL_DEBUG(DBG_MISC_WAIT, 2,(uint32_t)&p->p_evlist,0,0,0);

		if (error == 0)
			goto retry;
		if (error == ERESTART)
			error = EINTR;
		if (error == EWOULDBLOCK) {
			*retval = 1;
			error = 0;
		}
	}
	proc_unlock(p);

	KERNEL_DEBUG(DBG_MISC_WAIT|DBG_FUNC_END, 0,0,0,0,0);
	return (error);
}