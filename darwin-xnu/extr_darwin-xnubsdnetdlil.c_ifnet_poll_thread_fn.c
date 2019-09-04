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
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct mbuf {int dummy; } ;
struct ifnet_stat_increment_param {int packets_in; int bytes_in; } ;
struct ifnet {scalar_t__ if_poll_thread; int if_poll_active; scalar_t__ if_poll_req; struct timespec if_poll_cycle; int /*<<< orphan*/  if_poll_lock; int /*<<< orphan*/  (* if_input_poll ) (struct ifnet*,int /*<<< orphan*/ ,int,struct mbuf**,struct mbuf**,int*,int*) ;struct dlil_threading_info* if_inp; } ;
struct dlil_threading_info {scalar_t__ rxpoll_plim; int rxpoll_phiwat; int rxpoll_pavg; int rxpoll_pmax; int rxpoll_wavg; int rxpoll_bavg; int /*<<< orphan*/  rcvq_pkts; } ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  ifname ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int PSPIN ; 
 int PZERO ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (struct ifnet_stat_increment_param*,int) ; 
 int /*<<< orphan*/  current_thread () ; 
 int dlil_verbose ; 
 char* if_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_input_common (struct ifnet*,struct mbuf*,struct mbuf*,struct ifnet_stat_increment_param*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_set_poll_cycle (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int,char*,struct timespec*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  qlimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,int /*<<< orphan*/ ,int,struct mbuf**,struct mbuf**,int*,int*) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_terminate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ifnet_poll_thread_fn(void *v, wait_result_t w)
{
#pragma unused(w)
	struct dlil_threading_info *inp;
	struct ifnet *ifp = v;
	char ifname[IFNAMSIZ + 1];
	struct timespec *ts = NULL;
	struct ifnet_stat_increment_param s;

	snprintf(ifname, sizeof (ifname), "%s_poller",
	    if_name(ifp));
	bzero(&s, sizeof (s));

	lck_mtx_lock_spin(&ifp->if_poll_lock);

	inp = ifp->if_inp;
	VERIFY(inp != NULL);

	for (;;) {
		if (ifp->if_poll_thread != THREAD_NULL) {
			(void) msleep(&ifp->if_poll_thread, &ifp->if_poll_lock,
			    (PZERO - 1) | PSPIN, ifname, ts);
		}

		/* interface is detached (maybe while asleep)? */
		if (ifp->if_poll_thread == THREAD_NULL) {
			ifnet_set_poll_cycle(ifp, NULL);
			lck_mtx_unlock(&ifp->if_poll_lock);

			if (dlil_verbose) {
				printf("%s: poller thread terminated\n",
				    if_name(ifp));
			}

			/* for the extra refcnt from kernel_thread_start() */
			thread_deallocate(current_thread());
			/* this is the end */
			thread_terminate(current_thread());
			/* NOTREACHED */
			return;
		}

		ifp->if_poll_active = 1;
		for (;;) {
			struct mbuf *m_head, *m_tail;
			u_int32_t m_lim, m_cnt, m_totlen;
			u_int16_t req = ifp->if_poll_req;

			lck_mtx_unlock(&ifp->if_poll_lock);

			/*
			 * If no longer attached, there's nothing to do;
			 * else hold an IO refcnt to prevent the interface
			 * from being detached (will be released below.)
			 */
			if (!ifnet_is_attached(ifp, 1)) {
				lck_mtx_lock_spin(&ifp->if_poll_lock);
				break;
			}

			m_lim = (inp->rxpoll_plim != 0) ? inp->rxpoll_plim :
			    MAX((qlimit(&inp->rcvq_pkts)),
			    (inp->rxpoll_phiwat << 2));

			if (dlil_verbose > 1) {
				printf("%s: polling up to %d pkts, "
				    "pkts avg %d max %d, wreq avg %d, "
				    "bytes avg %d\n",
				    if_name(ifp), m_lim,
				    inp->rxpoll_pavg, inp->rxpoll_pmax,
				    inp->rxpoll_wavg, inp->rxpoll_bavg);
			}

			/* invoke the driver's input poll routine */
			((*ifp->if_input_poll)(ifp, 0, m_lim, &m_head, &m_tail,
			    &m_cnt, &m_totlen));

			if (m_head != NULL) {
				VERIFY(m_tail != NULL && m_cnt > 0);

				if (dlil_verbose > 1) {
					printf("%s: polled %d pkts, "
					    "pkts avg %d max %d, wreq avg %d, "
					    "bytes avg %d\n",
					    if_name(ifp), m_cnt,
					    inp->rxpoll_pavg, inp->rxpoll_pmax,
					    inp->rxpoll_wavg, inp->rxpoll_bavg);
				}

				/* stats are required for extended variant */
				s.packets_in = m_cnt;
				s.bytes_in = m_totlen;

				(void) ifnet_input_common(ifp, m_head, m_tail,
				    &s, TRUE, TRUE);
			} else {
				if (dlil_verbose > 1) {
					printf("%s: no packets, "
					    "pkts avg %d max %d, wreq avg %d, "
					    "bytes avg %d\n",
					    if_name(ifp), inp->rxpoll_pavg,
					    inp->rxpoll_pmax, inp->rxpoll_wavg,
					    inp->rxpoll_bavg);
				}

				(void) ifnet_input_common(ifp, NULL, NULL,
				    NULL, FALSE, TRUE);
			}

			/* Release the io ref count */
			ifnet_decr_iorefcnt(ifp);

			lck_mtx_lock_spin(&ifp->if_poll_lock);

			/* if there's no pending request, we're done */
			if (req == ifp->if_poll_req) {
				break;
			}
		}
		ifp->if_poll_req = 0;
		ifp->if_poll_active = 0;

		/*
		 * Wakeup N ns from now, else sleep indefinitely (ts = NULL)
		 * until ifnet_poll() is called again.
		 */
		ts = &ifp->if_poll_cycle;
		if (ts->tv_sec == 0 && ts->tv_nsec == 0)
			ts = NULL;
	}

	/* NOTREACHED */
}