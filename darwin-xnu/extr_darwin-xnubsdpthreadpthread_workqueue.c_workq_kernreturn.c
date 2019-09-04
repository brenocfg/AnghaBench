#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct workqueue {int /*<<< orphan*/  wq_event_manager_priority; } ;
struct workq_kernreturn_args {int options; int affinity; int prio; } ;
struct uthread {int uu_workq_flags; } ;
struct proc {int p_lflag; int /*<<< orphan*/  p_dispatchqueue_serialno_offset; } ;
typedef  int pthread_priority_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int P_LREGISTER ; 
 int THREAD_QOS_MIN_TIER_IMPORTANCE ; 
 int /*<<< orphan*/  THREAD_QOS_UNSPECIFIED ; 
 int THREAD_TAG_WORKQUEUE ; 
 int UT_WORKQ_DYING ; 
 int UT_WORKQ_OVERCOMMIT ; 
#define  WQOPS_QUEUE_NEWSPISUPP 134 
#define  WQOPS_QUEUE_REQTHREADS 133 
#define  WQOPS_SET_EVENT_MANAGER_PRIORITY 132 
#define  WQOPS_SHOULD_NARROW 131 
#define  WQOPS_THREAD_KEVENT_RETURN 130 
#define  WQOPS_THREAD_RETURN 129 
#define  WQOPS_THREAD_WORKLOOP_RETURN 128 
 int _PTHREAD_PRIORITY_FLAGS_MASK ; 
 int _PTHREAD_PRIORITY_SCHED_PRI_FLAG ; 
 int _PTHREAD_PRIORITY_SCHED_PRI_MASK ; 
 int _pthread_priority_relpri (int) ; 
 int /*<<< orphan*/  _pthread_priority_thread_qos (int) ; 
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 struct workqueue* proc_get_wqptr (struct proc*) ; 
 int thread_get_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_constrained_allowance (struct workqueue*,int /*<<< orphan*/ ,struct uthread*,int) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int workq_reqthreads (struct proc*,int,int) ; 
 int workq_thread_return (struct proc*,struct workq_kernreturn_args*,struct workqueue*) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

int
workq_kernreturn(struct proc *p, struct workq_kernreturn_args *uap, int32_t *retval)
{
	int options = uap->options;
	int arg2 = uap->affinity;
	int arg3 = uap->prio;
	struct workqueue *wq = proc_get_wqptr(p);
	int error = 0;

	if ((p->p_lflag & P_LREGISTER) == 0) {
		return EINVAL;
	}

	switch (options) {
	case WQOPS_QUEUE_NEWSPISUPP: {
		/*
		 * arg2 = offset of serialno into dispatch queue
		 * arg3 = kevent support
		 */
		int offset = arg2;
		if (arg3 & 0x01){
			// If we get here, then userspace has indicated support for kevent delivery.
		}

		p->p_dispatchqueue_serialno_offset = (uint64_t)offset;
		break;
	}
	case WQOPS_QUEUE_REQTHREADS: {
		/*
		 * arg2 = number of threads to start
		 * arg3 = priority
		 */
		error = workq_reqthreads(p, arg2, arg3);
		break;
	}
	case WQOPS_SET_EVENT_MANAGER_PRIORITY: {
		/*
		 * arg2 = priority for the manager thread
		 *
		 * if _PTHREAD_PRIORITY_SCHED_PRI_FLAG is set,
		 * the low bits of the value contains a scheduling priority
		 * instead of a QOS value
		 */
		pthread_priority_t pri = arg2;

		if (wq == NULL) {
			error = EINVAL;
			break;
		}

		/*
		 * Normalize the incoming priority so that it is ordered numerically.
		 */
		if (pri & _PTHREAD_PRIORITY_SCHED_PRI_FLAG) {
			pri &= (_PTHREAD_PRIORITY_SCHED_PRI_MASK |
					_PTHREAD_PRIORITY_SCHED_PRI_FLAG);
		} else {
			thread_qos_t qos = _pthread_priority_thread_qos(pri);
			int relpri = _pthread_priority_relpri(pri);
			if (relpri > 0 || relpri < THREAD_QOS_MIN_TIER_IMPORTANCE ||
					qos == THREAD_QOS_UNSPECIFIED) {
				error = EINVAL;
				break;
			}
			pri &= ~_PTHREAD_PRIORITY_FLAGS_MASK;
		}

		/*
		 * If userspace passes a scheduling priority, that wins over any QoS.
		 * Userspace should takes care not to lower the priority this way.
		 */
		workq_lock_spin(wq);
		if (wq->wq_event_manager_priority < (uint32_t)pri) {
			wq->wq_event_manager_priority = (uint32_t)pri;
		}
		workq_unlock(wq);
		break;
	}
	case WQOPS_THREAD_KEVENT_RETURN:
	case WQOPS_THREAD_WORKLOOP_RETURN:
	case WQOPS_THREAD_RETURN: {
		error = workq_thread_return(p, uap, wq);
		break;
	}

	case WQOPS_SHOULD_NARROW: {
		/*
		 * arg2 = priority to test
		 * arg3 = unused
		 */
		thread_t th = current_thread();
		struct uthread *uth = get_bsdthread_info(th);
		if (((thread_get_tag(th) & THREAD_TAG_WORKQUEUE) == 0) ||
				(uth->uu_workq_flags & (UT_WORKQ_DYING|UT_WORKQ_OVERCOMMIT))) {
			error = EINVAL;
			break;
		}

		thread_qos_t qos = _pthread_priority_thread_qos(arg2);
		if (qos == THREAD_QOS_UNSPECIFIED) {
			error = EINVAL;
			break;
		}
		workq_lock_spin(wq);
		bool should_narrow = !workq_constrained_allowance(wq, qos, uth, false);
		workq_unlock(wq);

		*retval = should_narrow;
		break;
	}
	default:
		error = EINVAL;
		break;
	}

	return (error);
}