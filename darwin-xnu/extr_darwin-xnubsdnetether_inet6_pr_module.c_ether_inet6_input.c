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
typedef  scalar_t__ u_int16_t ;
struct ip6aux {scalar_t__* ip6a_ehsrc; int /*<<< orphan*/  ip6a_flags; } ;
struct ifnet {int dummy; } ;
struct ether_header {int /*<<< orphan*/ * ether_shost; int /*<<< orphan*/ * ether_dhost; int /*<<< orphan*/  ether_type; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  ether_type ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EJUSTRETURN ; 
 int /*<<< orphan*/  ETHERTYPE_IPV6 ; 
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IP6A_HASEEN ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  etherbroadcastaddr ; 
 int /*<<< orphan*/  etherip6allnodes ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct ip6aux* ip6_addaux (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 struct ifnet* mbuf_pkthdr_rcvif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd6_llreach_set_reachable (struct ifnet*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ proto_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
ether_inet6_input(ifnet_t ifp, protocol_family_t protocol,
    mbuf_t packet, char *header)
{
#pragma unused(ifp, protocol)
	struct ether_header *eh = (struct ether_header *)(void *)header;
	u_int16_t ether_type;

	bcopy(&eh->ether_type, &ether_type, sizeof (ether_type));

	if (ether_type == htons(ETHERTYPE_IPV6)) {
		struct ifnet *mifp;
		/*
		 * Trust the ifp in the mbuf, rather than ifproto's
		 * since the packet could have been injected via
		 * a dlil_input_packet_list() using an ifp that is
		 * different than the one where the packet really
		 * came from.
		 */
		mifp = mbuf_pkthdr_rcvif(packet);

		/* Update L2 reachability record, if present (and not bcast) */
		if (bcmp(eh->ether_shost, etherbroadcastaddr,
		    ETHER_ADDR_LEN) != 0) {
			nd6_llreach_set_reachable(mifp, eh->ether_shost,
			    ETHER_ADDR_LEN);
		}

		/* Save the Ethernet source address for all-nodes multicasts */
		if (!bcmp(eh->ether_dhost, etherip6allnodes, ETHER_ADDR_LEN)) {
			struct ip6aux *ip6a;

			ip6a = ip6_addaux(packet);
			if (ip6a) {
				ip6a->ip6a_flags |= IP6A_HASEEN;
				bcopy(eh->ether_shost, ip6a->ip6a_ehsrc,
				    ETHER_ADDR_LEN);
			}
		}

		if (proto_input(protocol, packet) != 0)
			m_freem(packet);
	} else {
		m_freem(packet);
	}

	return (EJUSTRETURN);
}