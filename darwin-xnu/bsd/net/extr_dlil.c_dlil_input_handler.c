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
typedef  scalar_t__ u_int32_t ;
struct thread {int dummy; } ;
struct mbuf {int dummy; } ;
struct ifnet_stat_increment_param {scalar_t__ packets_in; scalar_t__ bytes_in; } ;
struct ifnet {scalar_t__ if_family; scalar_t__ if_type; struct dlil_threading_info* if_inp; } ;
struct dlil_threading_info {scalar_t__ wloop_thr; scalar_t__ poll_thr; scalar_t__ tag; scalar_t__ input_mbuf_cnt; int input_waiting; int /*<<< orphan*/  input_lck; int /*<<< orphan*/  wtot; scalar_t__ input_mit_tcall; int /*<<< orphan*/  rcvq_pkts; scalar_t__ net_affinity; } ;
struct dlil_main_threading_info {int /*<<< orphan*/  lo_rcvq_pkts; } ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int DLIL_INPUT_RUNNING ; 
 int DLIL_INPUT_WAITING ; 
 scalar_t__ IFNET_FAMILY_ETHERNET ; 
 scalar_t__ IFT_CELLULAR ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  _addq_multi (int /*<<< orphan*/ *,struct mbuf*,struct mbuf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlil_affinity_set (struct thread*,scalar_t__) ; 
 scalar_t__ dlil_input_sanity_check ; 
 int /*<<< orphan*/  dlil_input_stats_add (struct ifnet_stat_increment_param const*,struct dlil_threading_info*,scalar_t__) ; 
 int /*<<< orphan*/  dlil_input_stats_sync (struct ifnet*,struct dlil_threading_info*) ; 
 struct dlil_threading_info* dlil_main_input_thread ; 
 int /*<<< orphan*/  dlil_rcv_mit_interval ; 
 scalar_t__ dlil_rcv_mit_pkts_max ; 
 scalar_t__ dlil_rcv_mit_pkts_min ; 
 int /*<<< orphan*/  if_name (struct ifnet*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 struct ifnet* lo_ifp ; 
 struct mbuf* mbuf_nextpkt (struct mbuf*) ; 
 int /*<<< orphan*/  panic_plain (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_enter_delayed (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_isactive (scalar_t__) ; 
 int /*<<< orphan*/  thread_reference (struct thread*) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ ) ; 

errno_t
dlil_input_handler(struct ifnet *ifp, struct mbuf *m_head,
    struct mbuf *m_tail, const struct ifnet_stat_increment_param *s,
    boolean_t poll, struct thread *tp)
{
	struct dlil_threading_info *inp;
	u_int32_t m_cnt = s->packets_in;
	u_int32_t m_size = s->bytes_in;

	if ((inp = ifp->if_inp) == NULL)
		inp = dlil_main_input_thread;

	/*
	 * If there is a matching DLIL input thread associated with an
	 * affinity set, associate this thread with the same set.  We
	 * will only do this once.
	 */
	lck_mtx_lock_spin(&inp->input_lck);
	if (inp != dlil_main_input_thread && inp->net_affinity && tp != NULL &&
	    ((!poll && inp->wloop_thr == THREAD_NULL) ||
	    (poll && inp->poll_thr == THREAD_NULL))) {
		u_int32_t tag = inp->tag;

		if (poll) {
			VERIFY(inp->poll_thr == THREAD_NULL);
			inp->poll_thr = tp;
		} else {
			VERIFY(inp->wloop_thr == THREAD_NULL);
			inp->wloop_thr = tp;
		}
		lck_mtx_unlock(&inp->input_lck);

		/* Associate the current thread with the new affinity tag */
		(void) dlil_affinity_set(tp, tag);

		/*
		 * Take a reference on the current thread; during detach,
		 * we will need to refer to it in order to tear down its
		 * affinity.
		 */
		thread_reference(tp);
		lck_mtx_lock_spin(&inp->input_lck);
	}

	VERIFY(m_head != NULL || (m_tail == NULL && m_cnt == 0));

	/*
	 * Because of loopbacked multicast we cannot stuff the ifp in
	 * the rcvif of the packet header: loopback (lo0) packets use a
	 * dedicated list so that we can later associate them with lo_ifp
	 * on their way up the stack.  Packets for other interfaces without
	 * dedicated input threads go to the regular list.
	 */
	if (m_head != NULL) {
		if (inp == dlil_main_input_thread && ifp == lo_ifp) {
			struct dlil_main_threading_info *inpm =
			    (struct dlil_main_threading_info *)inp;
			_addq_multi(&inpm->lo_rcvq_pkts, m_head, m_tail,
			    m_cnt, m_size);
		} else {
			_addq_multi(&inp->rcvq_pkts, m_head, m_tail,
			    m_cnt, m_size);
		}
	}

#if IFNET_INPUT_SANITY_CHK
	if (dlil_input_sanity_check != 0) {
		u_int32_t count;
		struct mbuf *m0;

		for (m0 = m_head, count = 0; m0; m0 = mbuf_nextpkt(m0))
			count++;

		if (count != m_cnt) {
			panic_plain("%s: invalid packet count %d "
			    "(expected %d)\n", if_name(ifp),
			    count, m_cnt);
			/* NOTREACHED */
		}

		inp->input_mbuf_cnt += m_cnt;
	}
#endif /* IFNET_INPUT_SANITY_CHK */

	dlil_input_stats_add(s, inp, poll);
	/*
	 * If we're using the main input thread, synchronize the
	 * stats now since we have the interface context.  All
	 * other cases involving dedicated input threads will
	 * have their stats synchronized there.
	 */
	if (inp == dlil_main_input_thread)
		dlil_input_stats_sync(ifp, inp);

	if (inp->input_mit_tcall &&
	    qlen(&inp->rcvq_pkts) >= dlil_rcv_mit_pkts_min &&
	    qlen(&inp->rcvq_pkts) < dlil_rcv_mit_pkts_max &&
	    (ifp->if_family == IFNET_FAMILY_ETHERNET ||
	    ifp->if_type == IFT_CELLULAR)
	    ) {
		if (!thread_call_isactive(inp->input_mit_tcall)) {
			uint64_t deadline;
			clock_interval_to_deadline(dlil_rcv_mit_interval,
			    1, &deadline);
			(void) thread_call_enter_delayed(
			    inp->input_mit_tcall, deadline);
		}
	} else {
		inp->input_waiting |= DLIL_INPUT_WAITING;
		if (!(inp->input_waiting & DLIL_INPUT_RUNNING)) {
			inp->wtot++;
			wakeup_one((caddr_t)&inp->input_waiting);
		}
	}
	lck_mtx_unlock(&inp->input_lck);

	return (0);
}