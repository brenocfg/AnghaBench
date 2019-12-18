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
struct TYPE_2__ {int pkt_flags; } ;
struct mbuf {struct mbuf* m_nextpkt; TYPE_1__ m_pkthdr; } ;
struct ip_fw_args {int dummy; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ net_thread_marks_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 scalar_t__ IFNET_IS_INTCOPROC (struct ifnet*) ; 
 int /*<<< orphan*/  NET_THREAD_HELD_PF ; 
 int PKTF_LOOP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  intcoproc_unrestricted ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ ) ; 
 struct ifnet* lo_ifp ; 
 scalar_t__ net_thread_marks_none ; 
 int /*<<< orphan*/  net_thread_marks_pop (scalar_t__) ; 
 scalar_t__ net_thread_marks_push (int /*<<< orphan*/ ) ; 
 int pf_inet6_hook (struct ifnet*,struct mbuf**,int,struct ip_fw_args*) ; 
 int pf_inet_hook (struct ifnet*,struct mbuf**,int,struct ip_fw_args*) ; 
 int /*<<< orphan*/  pf_is_enabled ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/  pf_perim_lock ; 

int
pf_af_hook(struct ifnet *ifp, struct mbuf **mppn, struct mbuf **mp,
    unsigned int af, int input, struct ip_fw_args *fwa)
{
	int error = 0;
	struct mbuf *nextpkt;
	net_thread_marks_t marks;
	struct ifnet * pf_ifp = ifp;

	/* Always allow traffic on co-processor interfaces. */
	if (!intcoproc_unrestricted && ifp && IFNET_IS_INTCOPROC(ifp))
		return (0);

	marks = net_thread_marks_push(NET_THREAD_HELD_PF);

	if (marks != net_thread_marks_none) {
		lck_rw_lock_shared(pf_perim_lock);
		if (!pf_is_enabled)
			goto done;
		lck_mtx_lock(pf_lock);
	}

	if (mppn != NULL && *mppn != NULL)
		VERIFY(*mppn == *mp);
	if ((nextpkt = (*mp)->m_nextpkt) != NULL)
		(*mp)->m_nextpkt = NULL;

        /*
         * For packets destined to locally hosted IP address
         * ip_output_list sets Mbuf's pkt header's rcvif to
         * the interface hosting the IP address.
         * While on the output path ifp passed to pf_af_hook
         * to such local communication is the loopback interface,
         * the input path derives ifp from mbuf packet header's
         * rcvif.
         * This asymmetry caues issues with PF.
         * To handle that case, we have a limited change here to
         * pass interface as loopback if packets are looped in.
         */
	if (input && ((*mp)->m_pkthdr.pkt_flags & PKTF_LOOP)) {
		pf_ifp = lo_ifp;
	}

	switch (af) {
#if INET
	case AF_INET: {
		error = pf_inet_hook(pf_ifp, mp, input, fwa);
		break;
	}
#endif /* INET */
#if INET6
	case AF_INET6:
		error = pf_inet6_hook(pf_ifp, mp, input, fwa);
		break;
#endif /* INET6 */
	default:
		break;
	}

	/* When packet valid, link to the next packet */
	if (*mp != NULL && nextpkt != NULL) {
		struct mbuf *m = *mp;
		while (m->m_nextpkt != NULL)
			m = m->m_nextpkt;
		m->m_nextpkt = nextpkt;
	}
	/* Fix up linkage of previous packet in the chain */
	if (mppn != NULL) {
		if (*mp != NULL)
			*mppn = *mp;
		else
			*mppn = nextpkt;
	}

	if (marks != net_thread_marks_none)
		lck_mtx_unlock(pf_lock);

done:
	if (marks != net_thread_marks_none)
		lck_rw_done(pf_perim_lock);

	net_thread_marks_pop(marks);
	return (error);
}