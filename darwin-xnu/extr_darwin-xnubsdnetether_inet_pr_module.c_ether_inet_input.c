#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
struct ether_header {scalar_t__ ether_type; int /*<<< orphan*/  ether_shost; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_9__ {struct TYPE_9__* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EJUSTRETURN ; 
 int /*<<< orphan*/  ETHERTYPE_ARP ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  arp_llreach_set_reachable (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_inet_arp_input (struct ifnet*,TYPE_1__*) ; 
 int /*<<< orphan*/  etherbroadcastaddr ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_freem (TYPE_1__*) ; 
 int /*<<< orphan*/  mbuf_freem_list (TYPE_1__*) ; 
 struct ether_header* mbuf_pkthdr_header (TYPE_1__*) ; 
 struct ifnet* mbuf_pkthdr_rcvif (TYPE_1__*) ; 
 scalar_t__ proto_input (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static errno_t
ether_inet_input(ifnet_t ifp, protocol_family_t	protocol_family,
    mbuf_t m_list)
{
#pragma unused(ifp, protocol_family)
	mbuf_t	m;
	mbuf_t	*tailptr = &m_list;
	mbuf_t	nextpkt;

	/* Strip ARP and non-IP packets out of the list */
	for (m = m_list; m; m = nextpkt) {
		struct ether_header *eh = mbuf_pkthdr_header(m);
		struct ifnet *mifp;

		/*
		 * Trust the ifp in the mbuf, rather than ifproto's
		 * since the packet could have been injected via
		 * a dlil_input_packet_list() using an ifp that is
		 * different than the one where the packet really
		 * came from.
		 */
		mifp = mbuf_pkthdr_rcvif(m);

		nextpkt = m->m_nextpkt;

		if (eh->ether_type == htons(ETHERTYPE_IP)) {
			/*
			 * Update L2 reachability record, if present
			 * (and if not a broadcast sender).
			 */
			if (bcmp(eh->ether_shost, etherbroadcastaddr,
			    ETHER_ADDR_LEN) != 0) {
				arp_llreach_set_reachable(mifp, eh->ether_shost,
				    ETHER_ADDR_LEN);
			}
			/* put this packet in the list */
			*tailptr = m;
			tailptr = &m->m_nextpkt;
		} else {
			/* Pass ARP packets to arp input */
			m->m_nextpkt = NULL;
			if (eh->ether_type == htons(ETHERTYPE_ARP))
				ether_inet_arp_input(mifp, m);
			else
				mbuf_freem(m);
		}
	}

	*tailptr = NULL;

	/* Pass IP list to ip input */
	if (m_list != NULL && proto_input(PF_INET, m_list) != 0) {
		mbuf_freem_list(m_list);
	}

	return (EJUSTRETURN);
}