#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ u_int64_t ;
struct timespec {int dummy; } ;
struct TYPE_2__ {int pkt_flags; int /*<<< orphan*/  pkt_flowsrc; scalar_t__ pkt_timestamp; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; int /*<<< orphan*/ * m_nextpkt; } ;
struct ifnet {int if_eflags; int if_start_delay_timeout; scalar_t__ if_start_delay_swin; int if_start_delay_cnt; int if_start_delay_idle; int if_start_delay_qlen; int /*<<< orphan*/  if_snd; void* if_rt_sendts; void* if_fg_sendts; } ;
typedef  int errno_t ;
typedef  int classq_pkt_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EQFULL ; 
 int EQSUSPENDED ; 
 int /*<<< orphan*/  FLOWSRC_INPCB ; 
 int IFEF_DELAY_START ; 
 int IFEF_ENQUEUE_MULTI ; 
 int IFEF_TXSTART ; 
 int M_PKTHDR ; 
 int PKTF_FLOW_ID ; 
 int PKTF_SO_BACKGROUND ; 
 int PKTF_SO_REALTIME ; 
 int PKTF_TS_VALID ; 
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 void* _net_uptime ; 
 int ifclassq_enqueue (int /*<<< orphan*/ *,struct mbuf*,int const,scalar_t__*) ; 
 int /*<<< orphan*/  ifnet_delay_start_disabled ; 
 int /*<<< orphan*/  ifnet_start (struct ifnet*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int /*<<< orphan*/  net_timernsec (struct timespec*,scalar_t__*) ; 

__attribute__((used)) static inline errno_t
ifnet_enqueue_common(struct ifnet *ifp, void *p, classq_pkt_type_t ptype,
    boolean_t flush, boolean_t *pdrop)
{
	volatile uint64_t *fg_ts = NULL;
	volatile uint64_t *rt_ts = NULL;
	struct mbuf *m = p;
	struct timespec now;
	u_int64_t now_nsec = 0;
	int error = 0;

	ASSERT(ifp->if_eflags & IFEF_TXSTART);

	/*
	 * If packet already carries a timestamp, either from dlil_output()
	 * or from flowswitch, use it here.  Otherwise, record timestamp.
	 * PKTF_TS_VALID is always cleared prior to entering classq, i.e.
	 * the timestamp value is used internally there.
	 */
	switch (ptype) {
	case QP_MBUF:
		ASSERT(m->m_flags & M_PKTHDR);
		ASSERT(m->m_nextpkt == NULL);

		if (!(m->m_pkthdr.pkt_flags & PKTF_TS_VALID) ||
		    m->m_pkthdr.pkt_timestamp == 0) {
			nanouptime(&now);
			net_timernsec(&now, &now_nsec);
			m->m_pkthdr.pkt_timestamp = now_nsec;
		}
		m->m_pkthdr.pkt_flags &= ~PKTF_TS_VALID;
		/*
		 * If the packet service class is not background,
		 * update the timestamp to indicate recent activity
		 * on a foreground socket.
		 */
		if ((m->m_pkthdr.pkt_flags & PKTF_FLOW_ID) &&
		    m->m_pkthdr.pkt_flowsrc == FLOWSRC_INPCB) {
			if (!(m->m_pkthdr.pkt_flags & PKTF_SO_BACKGROUND)) {
				ifp->if_fg_sendts = _net_uptime;
				if (fg_ts != NULL)
					*fg_ts = _net_uptime;
			}
			if (m->m_pkthdr.pkt_flags & PKTF_SO_REALTIME) {
				ifp->if_rt_sendts = _net_uptime;
				if (rt_ts != NULL)
					*rt_ts = _net_uptime;
			}
		}
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	if (ifp->if_eflags & IFEF_ENQUEUE_MULTI) {
		if (now_nsec == 0) {
			nanouptime(&now);
			net_timernsec(&now, &now_nsec);
		}
		/*
		 * If the driver chose to delay start callback for
		 * coalescing multiple packets, Then use the following
		 * heuristics to make sure that start callback will
		 * be delayed only when bulk data transfer is detected.
		 * 1. number of packets enqueued in (delay_win * 2) is
		 * greater than or equal to the delay qlen.
		 * 2. If delay_start is enabled it will stay enabled for
		 * another 10 idle windows. This is to take into account
		 * variable RTT and burst traffic.
		 * 3. If the time elapsed since last enqueue is more
		 * than 200ms we disable delaying start callback. This is
		 * is to take idle time into account.
		 */
		u_int64_t dwin = (ifp->if_start_delay_timeout << 1);
		if (ifp->if_start_delay_swin > 0) {
			if ((ifp->if_start_delay_swin + dwin) > now_nsec) {
				ifp->if_start_delay_cnt++;
			} else if ((now_nsec - ifp->if_start_delay_swin)
			    >= (200 * 1000 * 1000)) {
				ifp->if_start_delay_swin = now_nsec;
				ifp->if_start_delay_cnt = 1;
				ifp->if_start_delay_idle = 0;
				if (ifp->if_eflags & IFEF_DELAY_START) {
					ifp->if_eflags &=
					    ~(IFEF_DELAY_START);
					ifnet_delay_start_disabled++;
				}
			} else {
				if (ifp->if_start_delay_cnt >=
				    ifp->if_start_delay_qlen) {
					ifp->if_eflags |= IFEF_DELAY_START;
					ifp->if_start_delay_idle = 0;
				} else {
					if (ifp->if_start_delay_idle >= 10) {
						ifp->if_eflags &= ~(IFEF_DELAY_START);
						ifnet_delay_start_disabled++;
					} else {
						ifp->if_start_delay_idle++;
					}
				}
				ifp->if_start_delay_swin = now_nsec;
				ifp->if_start_delay_cnt = 1;
			}
		} else {
			ifp->if_start_delay_swin = now_nsec;
			ifp->if_start_delay_cnt = 1;
			ifp->if_start_delay_idle = 0;
			ifp->if_eflags &= ~(IFEF_DELAY_START);
		}
	} else {
		ifp->if_eflags &= ~(IFEF_DELAY_START);
	}

	switch (ptype) {
	case QP_MBUF:
		/* enqueue the packet (caller consumes object) */
		error = ifclassq_enqueue(&ifp->if_snd, m, QP_MBUF, pdrop);
		m = NULL;
		break;


	default:
		break;
	}

	/*
	 * Tell the driver to start dequeueing; do this even when the queue
	 * for the packet is suspended (EQSUSPENDED), as the driver could still
	 * be dequeueing from other unsuspended queues.
	 */
	if (!(ifp->if_eflags & IFEF_ENQUEUE_MULTI) &&
	    ((error == 0 && flush) || error == EQFULL || error == EQSUSPENDED))
		ifnet_start(ifp);

	return (error);
}