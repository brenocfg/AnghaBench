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
typedef  int /*<<< orphan*/  wait_result_t ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  thread_name ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct thread {int dummy; } ;
struct ifclassq {int dummy; } ;
struct ifnet {char* if_xname; int if_start_active; scalar_t__ if_start_req; int if_eflags; int if_start_delayed; scalar_t__ if_start_delay_qlen; int if_start_flags; scalar_t__ if_start_delay_timeout; struct timespec if_start_cycle; int /*<<< orphan*/  if_start_lock; int /*<<< orphan*/  (* if_start ) (struct ifnet*) ;struct thread* if_start_thread; struct ifclassq if_snd; } ;
struct dlil_threading_info {scalar_t__ tag; int /*<<< orphan*/  input_lck; struct thread* wloop_thr; struct thread* poll_thr; scalar_t__ net_affinity; } ;
typedef  int /*<<< orphan*/  ifname ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_IS_EMPTY (struct ifclassq*) ; 
 scalar_t__ IFCQ_LEN (struct ifclassq*) ; 
 scalar_t__ IFCQ_TBR_IS_ENABLED (struct ifclassq*) ; 
 int IFEF_DELAY_START ; 
 int IFEF_ENQUEUE_MULTI ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int IFSF_FLOW_CONTROLLED ; 
 int MAXTHREADNAMESIZE ; 
 int PSPIN ; 
 int PZERO ; 
 struct thread* THREAD_NULL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 struct thread* current_thread () ; 
 int /*<<< orphan*/  dlil_affinity_set (struct thread*,scalar_t__) ; 
 struct dlil_threading_info* dlil_main_input_thread ; 
 scalar_t__ dlil_verbose ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_purge (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_set_start_cycle (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_start_delayed ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 struct ifnet* lo_ifp ; 
 int /*<<< orphan*/  msleep (struct thread**,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 
 int /*<<< orphan*/  thread_deallocate (struct thread*) ; 
 int /*<<< orphan*/  thread_set_thread_name (struct thread*,char*) ; 
 int /*<<< orphan*/  thread_terminate (struct thread*) ; 

__attribute__((used)) static void
ifnet_start_thread_fn(void *v, wait_result_t w)
{
#pragma unused(w)
	struct ifnet *ifp = v;
	char ifname[IFNAMSIZ + 1];
	char thread_name[MAXTHREADNAMESIZE];
	struct timespec *ts = NULL;
	struct ifclassq *ifq = &ifp->if_snd;
	struct timespec delay_start_ts;

	/* Construct the name for this thread, and then apply it. */
	bzero(thread_name, sizeof(thread_name));
	(void) snprintf(thread_name, sizeof (thread_name),
	    "ifnet_start_%s", ifp->if_xname);
	thread_set_thread_name(ifp->if_start_thread, thread_name);

	/*
	 * Treat the dedicated starter thread for lo0 as equivalent to
	 * the driver workloop thread; if net_affinity is enabled for
	 * the main input thread, associate this starter thread to it
	 * by binding them with the same affinity tag.  This is done
	 * only once (as we only have one lo_ifp which never goes away.)
	 */
	if (ifp == lo_ifp) {
		struct dlil_threading_info *inp = dlil_main_input_thread;
		struct thread *tp = current_thread();

		lck_mtx_lock(&inp->input_lck);
		if (inp->net_affinity) {
			u_int32_t tag = inp->tag;

			VERIFY(inp->wloop_thr == THREAD_NULL);
			VERIFY(inp->poll_thr == THREAD_NULL);
			inp->wloop_thr = tp;
			lck_mtx_unlock(&inp->input_lck);

			/* Associate this thread with the affinity tag */
			(void) dlil_affinity_set(tp, tag);
		} else {
			lck_mtx_unlock(&inp->input_lck);
		}
	}

	(void) snprintf(ifname, sizeof (ifname), "%s_starter", if_name(ifp));

	lck_mtx_lock_spin(&ifp->if_start_lock);

	for (;;) {
		if (ifp->if_start_thread != NULL) {
			(void) msleep(&ifp->if_start_thread,
			    &ifp->if_start_lock,
			    (PZERO - 1) | PSPIN, ifname, ts);
		}
		/* interface is detached? */
		if (ifp->if_start_thread == THREAD_NULL) {
			ifnet_set_start_cycle(ifp, NULL);
			lck_mtx_unlock(&ifp->if_start_lock);
			ifnet_purge(ifp);

			if (dlil_verbose) {
				printf("%s: starter thread terminated\n",
				    if_name(ifp));
			}

			/* for the extra refcnt from kernel_thread_start() */
			thread_deallocate(current_thread());
			/* this is the end */
			thread_terminate(current_thread());
			/* NOTREACHED */
			return;
		}

		ifp->if_start_active = 1;

		for (;;) {
			u_int32_t req = ifp->if_start_req;
			if (!IFCQ_IS_EMPTY(ifq) &&
			    (ifp->if_eflags & IFEF_ENQUEUE_MULTI) &&
			    ifp->if_start_delayed == 0 &&
			    IFCQ_LEN(ifq) < ifp->if_start_delay_qlen &&
			    (ifp->if_eflags & IFEF_DELAY_START)) {
				ifp->if_start_delayed = 1;
				ifnet_start_delayed++;
				break;
			} else {
				ifp->if_start_delayed = 0;
			}
			lck_mtx_unlock(&ifp->if_start_lock);

			/*
			 * If no longer attached, don't call start because ifp
			 * is being destroyed; else hold an IO refcnt to
			 * prevent the interface from being detached (will be
			 * released below.)
			 */
			if (!ifnet_is_attached(ifp, 1)) {
				lck_mtx_lock_spin(&ifp->if_start_lock);
				break;
			}

			/* invoke the driver's start routine */
			((*ifp->if_start)(ifp));

			/*
			 * Release the io ref count taken by ifnet_is_attached.
			 */
			ifnet_decr_iorefcnt(ifp);

			lck_mtx_lock_spin(&ifp->if_start_lock);

			/*
			 * If there's no pending request or if the
			 * interface has been disabled, we're done.
			 */
			if (req == ifp->if_start_req ||
			    (ifp->if_start_flags & IFSF_FLOW_CONTROLLED)) {
				break;
			}
		}

		ifp->if_start_req = 0;
		ifp->if_start_active = 0;

		/*
		 * Wakeup N ns from now if rate-controlled by TBR, and if
		 * there are still packets in the send queue which haven't
		 * been dequeued so far; else sleep indefinitely (ts = NULL)
		 * until ifnet_start() is called again.
		 */
		ts = ((IFCQ_TBR_IS_ENABLED(ifq) && !IFCQ_IS_EMPTY(ifq)) ?
		    &ifp->if_start_cycle : NULL);

		if (ts == NULL && ifp->if_start_delayed == 1) {
			delay_start_ts.tv_sec = 0;
			delay_start_ts.tv_nsec = ifp->if_start_delay_timeout;
			ts = &delay_start_ts;
		}

		if (ts != NULL && ts->tv_sec == 0 && ts->tv_nsec == 0)
			ts = NULL;
	}

	/* NOTREACHED */
}