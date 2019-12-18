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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  thread_name ;
struct mbuf {int dummy; } ;
struct ifnet {char* if_xname; int if_eflags; } ;
struct dlil_threading_info {scalar_t__ mode; int input_waiting; int /*<<< orphan*/  input_lck; scalar_t__ wtot; int /*<<< orphan*/  rcvq_pkts; int /*<<< orphan*/  input_name; int /*<<< orphan*/  input_thr; struct ifnet* ifp; } ;

/* Variables and functions */
 int DLIL_INPUT_RUNNING ; 
 int DLIL_INPUT_TERMINATE ; 
 int DLIL_INPUT_WAITING ; 
 int DLIL_PROTO_REGISTER ; 
 int DLIL_PROTO_WAITING ; 
 int IFEF_RXPOLL ; 
 scalar_t__ IFNET_MODEL_INPUT_POLL_OFF ; 
 int MAXTHREADNAMESIZE ; 
 int PSPIN ; 
 int PZERO ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct mbuf* _getq_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  dlil_input_packet_list_extended (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dlil_input_stats_sync (struct ifnet*,struct dlil_threading_info*) ; 
 struct dlil_threading_info* dlil_main_input_thread ; 
 int /*<<< orphan*/  dlil_terminate_input_thread (struct dlil_threading_info*) ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbuf_freem_list (struct mbuf*) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_rxpoll ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  thread_set_thread_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dlil_input_thread_func(void *v, wait_result_t w)
{
#pragma unused(w)
	char thread_name[MAXTHREADNAMESIZE];
	struct dlil_threading_info *inp = v;
	struct ifnet *ifp = inp->ifp;

	/* Construct the name for this thread, and then apply it. */
	bzero(thread_name, sizeof(thread_name));
	snprintf(thread_name, sizeof(thread_name), "dlil_input_%s", ifp->if_xname);
	thread_set_thread_name(inp->input_thr, thread_name);

	VERIFY(inp != dlil_main_input_thread);
	VERIFY(ifp != NULL);
	VERIFY(!(ifp->if_eflags & IFEF_RXPOLL) || !net_rxpoll);
	VERIFY(inp->mode == IFNET_MODEL_INPUT_POLL_OFF);

	while (1) {
		struct mbuf *m = NULL;
		u_int32_t m_cnt;

		lck_mtx_lock_spin(&inp->input_lck);

		/* Wait until there is work to be done */
		while (!(inp->input_waiting & ~DLIL_INPUT_RUNNING)) {
			inp->input_waiting &= ~DLIL_INPUT_RUNNING;
			(void) msleep(&inp->input_waiting, &inp->input_lck,
			    (PZERO - 1) | PSPIN, inp->input_name, NULL);
		}

		inp->input_waiting |= DLIL_INPUT_RUNNING;
		inp->input_waiting &= ~DLIL_INPUT_WAITING;

		/*
		 * Protocol registration and injection must always use
		 * the main input thread; in theory the latter can utilize
		 * the corresponding input thread where the packet arrived
		 * on, but that requires our knowing the interface in advance
		 * (and the benefits might not worth the trouble.)
		 */
		VERIFY(!(inp->input_waiting &
		    (DLIL_PROTO_WAITING|DLIL_PROTO_REGISTER)));

		/* Packets for this interface */
		m_cnt = qlen(&inp->rcvq_pkts);
		m = _getq_all(&inp->rcvq_pkts, NULL, NULL, NULL);

		if (inp->input_waiting & DLIL_INPUT_TERMINATE) {
			lck_mtx_unlock(&inp->input_lck);

			/* Free up pending packets */
			if (m != NULL)
				mbuf_freem_list(m);

			dlil_terminate_input_thread(inp);
			/* NOTREACHED */
			return;
		}

		inp->wtot = 0;

			dlil_input_stats_sync(ifp, inp);

		lck_mtx_unlock(&inp->input_lck);

		/*
		 * NOTE warning %%% attention !!!!
		 * We should think about putting some thread starvation
		 * safeguards if we deal with long chains of packets.
		 */
		if (m != NULL)
			dlil_input_packet_list_extended(NULL, m,
			    m_cnt, inp->mode);
	}

	/* NOTREACHED */
	VERIFY(0);	/* we should never get here */
}