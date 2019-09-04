#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u_int32_t ;
struct TYPE_3__ {char* pkt_hdr; int pkt_flags; int csum_flags; int csum_rx_start; scalar_t__ csum_data; struct ifnet* rcvif; } ;
struct mbuf {char* m_data; int m_flags; struct mbuf* m_nextpkt; TYPE_1__ m_pkthdr; } ;
struct ifnet {int if_eflags; int (* if_demux ) (struct ifnet*,struct mbuf*,char*,scalar_t__*) ;int if_type; int if_flags; scalar_t__ if_updatemcasts; int /*<<< orphan*/  if_imcasts; int /*<<< orphan*/ * if_bridge; } ;
struct if_proto {scalar_t__ protocol_family; struct ifnet* ifp; } ;
struct ether_header {int /*<<< orphan*/  ether_type; } ;
typedef  scalar_t__ protocol_family_t ;
typedef  struct mbuf* mbuf_t ;
typedef  struct ifnet* ifnet_t ;
typedef  scalar_t__ ifnet_model_t ;
typedef  char* caddr_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  ip6s_clat464_in_drop; int /*<<< orphan*/  ip6s_clat464_in_v4_drop; } ;

/* Variables and functions */
 int CSUM_DATA_VALID ; 
 int CSUM_PARTIAL ; 
 int CSUM_VLAN_TAG_VALID ; 
 int DBG_FNC_DLIL_INPUT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  ETHERTYPE_IP ; 
 scalar_t__ ETHERTYPE_IPV6 ; 
 int /*<<< orphan*/  ETHER_HDR_LEN ; 
 int IFEF_RXPOLL ; 
 int IFF_LOOPBACK ; 
 scalar_t__ IFNET_MODEL_INPUT_POLL_ON ; 
#define  IFT_CELLULAR 129 
#define  IFT_ETHER 128 
 scalar_t__ IS_INTF_CLAT46 (struct ifnet*) ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_INPUT_CHECK (struct mbuf*,struct ifnet*) ; 
 int M_BCAST ; 
 int /*<<< orphan*/  M_LEADINGSPACE (struct mbuf*) ; 
 int M_MCAST ; 
 int M_PROMISC ; 
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 int PKTF_IFAINFO ; 
 int PKTF_LOOP ; 
 int PKTF_TS_VALID ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ clat_debug ; 
 int dlil_clat64 (struct ifnet*,scalar_t__*,struct mbuf**) ; 
 int /*<<< orphan*/  dlil_ifproto_input (struct if_proto*,struct mbuf*) ; 
 int /*<<< orphan*/  dlil_input_cksum_dbg (struct ifnet*,struct mbuf*,char*,scalar_t__) ; 
 int dlil_interface_filters_input (struct ifnet*,struct mbuf**,char**,scalar_t__) ; 
 scalar_t__ dlil_is_clat_needed (scalar_t__,struct mbuf*) ; 
 struct if_proto* find_attached_proto (struct ifnet*,scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ hwcksum_dbg ; 
 int /*<<< orphan*/  hwcksum_in_invalidated ; 
 scalar_t__ if_mcasts_update (struct ifnet*) ; 
 int /*<<< orphan*/  if_proto_free (struct if_proto*) ; 
 int /*<<< orphan*/  if_proto_ref (struct if_proto*) ; 
 int if_rxpoll_interval_pkts ; 
 int /*<<< orphan*/  ifnet_decr_iorefcnt (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_is_attached (struct ifnet*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_poll (struct ifnet*) ; 
 int /*<<< orphan*/  ifp_inc_traffic_class_in (struct ifnet*,struct mbuf*) ; 
 TYPE_2__ ip6stat ; 
 struct ifnet* lo_ifp ; 
 int /*<<< orphan*/  m_classifier_init (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 scalar_t__ mbuf_data (struct mbuf*) ; 
 scalar_t__ mbuf_datastart (struct mbuf*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pktap_input (struct ifnet*,scalar_t__,struct mbuf*,char*) ; 
 int stub1 (struct ifnet*,struct mbuf*,char*,scalar_t__*) ; 

__attribute__((used)) static void
dlil_input_packet_list_common(struct ifnet *ifp_param, struct mbuf *m,
    u_int32_t cnt, ifnet_model_t mode, boolean_t ext)
{
	int error = 0;
	protocol_family_t protocol_family;
	mbuf_t next_packet;
	ifnet_t	ifp = ifp_param;
	char *frame_header = NULL;
	struct if_proto	*last_ifproto = NULL;
	mbuf_t pkt_first = NULL;
	mbuf_t *pkt_next = NULL;
	u_int32_t poll_thresh = 0, poll_ival = 0;

	KERNEL_DEBUG(DBG_FNC_DLIL_INPUT | DBG_FUNC_START, 0, 0, 0, 0, 0);

	if (ext && mode == IFNET_MODEL_INPUT_POLL_ON && cnt > 1 &&
	    (poll_ival = if_rxpoll_interval_pkts) > 0)
		poll_thresh = cnt;

	while (m != NULL) {
		struct if_proto *ifproto = NULL;
		int iorefcnt = 0;
		uint32_t pktf_mask;	/* pkt flags to preserve */

		if (ifp_param == NULL)
			ifp = m->m_pkthdr.rcvif;

		if ((ifp->if_eflags & IFEF_RXPOLL) && poll_thresh != 0 &&
		    poll_ival > 0 && (--poll_thresh % poll_ival) == 0)
			ifnet_poll(ifp);

		/* Check if this mbuf looks valid */
		MBUF_INPUT_CHECK(m, ifp);

		next_packet = m->m_nextpkt;
		m->m_nextpkt = NULL;
		frame_header = m->m_pkthdr.pkt_hdr;
		m->m_pkthdr.pkt_hdr = NULL;

		/*
		 * Get an IO reference count if the interface is not
		 * loopback (lo0) and it is attached; lo0 never goes
		 * away, so optimize for that.
		 */
		if (ifp != lo_ifp) {
			if (!ifnet_is_attached(ifp, 1)) {
				m_freem(m);
				goto next;
			}
			iorefcnt = 1;
			/*
			 * Preserve the time stamp if it was set.
			 */
			pktf_mask = PKTF_TS_VALID;
		} else {
			/*
			 * If this arrived on lo0, preserve interface addr
			 * info to allow for connectivity between loopback
			 * and local interface addresses.
			 */
			pktf_mask = (PKTF_LOOP|PKTF_IFAINFO);
		}

		/* make sure packet comes in clean */
		m_classifier_init(m, pktf_mask);

		ifp_inc_traffic_class_in(ifp, m);

		/* find which protocol family this packet is for */
		ifnet_lock_shared(ifp);
		error = (*ifp->if_demux)(ifp, m, frame_header,
		    &protocol_family);
		ifnet_lock_done(ifp);
		if (error != 0) {
			if (error == EJUSTRETURN)
				goto next;
			protocol_family = 0;
		}

		pktap_input(ifp, protocol_family, m, frame_header);

		/* Drop v4 packets received on CLAT46 enabled interface */
		if (protocol_family == PF_INET && IS_INTF_CLAT46(ifp)) {
			m_freem(m);
			ip6stat.ip6s_clat464_in_v4_drop++;
			goto next;
		}

		/* Translate the packet if it is received on CLAT interface */
		if (protocol_family == PF_INET6 && IS_INTF_CLAT46(ifp)
		    && dlil_is_clat_needed(protocol_family, m)) {
			char *data = NULL;
			struct ether_header eh;
			struct ether_header *ehp = NULL;

			if (ifp->if_type == IFT_ETHER) {
				ehp = (struct ether_header *)(void *)frame_header;
				/* Skip RX Ethernet packets if they are not IPV6 */
				if (ntohs(ehp->ether_type) != ETHERTYPE_IPV6)
					goto skip_clat;

				/* Keep a copy of frame_header for Ethernet packets */
				bcopy(frame_header, (caddr_t)&eh, ETHER_HDR_LEN);
			}
			error = dlil_clat64(ifp, &protocol_family, &m);
			data = (char *) mbuf_data(m);
			if (error != 0) {
				m_freem(m);
				ip6stat.ip6s_clat464_in_drop++;
				goto next;
			}
			/* Native v6 should be No-op */
			if (protocol_family != PF_INET)
				goto skip_clat;

			/* Do this only for translated v4 packets. */
			switch (ifp->if_type) {
			case IFT_CELLULAR:
				frame_header = data;
				break;
			case IFT_ETHER:
				/*
				 * Drop if the mbuf doesn't have enough
				 * space for Ethernet header
				 */
				if (M_LEADINGSPACE(m) < ETHER_HDR_LEN) {
					m_free(m);
					ip6stat.ip6s_clat464_in_drop++;
					goto next;
				}
				/*
				 * Set the frame_header ETHER_HDR_LEN bytes
				 * preceeding the data pointer. Change
				 * the ether_type too.
				 */
				frame_header = data - ETHER_HDR_LEN;
				eh.ether_type = htons(ETHERTYPE_IP);
				bcopy((caddr_t)&eh, frame_header, ETHER_HDR_LEN);
				break;
			}
		}
skip_clat:
		if (hwcksum_dbg != 0 && !(ifp->if_flags & IFF_LOOPBACK) &&
		    !(m->m_pkthdr.pkt_flags & PKTF_LOOP))
			dlil_input_cksum_dbg(ifp, m, frame_header,
			    protocol_family);

		/*
		 * For partial checksum offload, we expect the driver to
		 * set the start offset indicating the start of the span
		 * that is covered by the hardware-computed checksum;
		 * adjust this start offset accordingly because the data
		 * pointer has been advanced beyond the link-layer header.
		 *
		 * Don't adjust if the interface is a bridge member, as
		 * the adjustment will occur from the context of the
		 * bridge interface during input.
		 */
		if (ifp->if_bridge == NULL && (m->m_pkthdr.csum_flags &
		    (CSUM_DATA_VALID | CSUM_PARTIAL)) ==
		    (CSUM_DATA_VALID | CSUM_PARTIAL)) {
			int adj;
			if (frame_header == NULL ||
			    frame_header < (char *)mbuf_datastart(m) ||
			    frame_header > (char *)m->m_data ||
			    (adj = (m->m_data - frame_header)) >
			    m->m_pkthdr.csum_rx_start) {
				m->m_pkthdr.csum_data = 0;
				m->m_pkthdr.csum_flags &= ~CSUM_DATA_VALID;
				hwcksum_in_invalidated++;
			} else {
				m->m_pkthdr.csum_rx_start -= adj;
			}
		}

		if (clat_debug)
			pktap_input(ifp, protocol_family, m, frame_header);

		if (m->m_flags & (M_BCAST|M_MCAST))
			atomic_add_64(&ifp->if_imcasts, 1);

		/* run interface filters, exclude VLAN packets PR-3586856 */
		if ((m->m_pkthdr.csum_flags & CSUM_VLAN_TAG_VALID) == 0) {
			error = dlil_interface_filters_input(ifp, &m,
			    &frame_header, protocol_family);
			if (error != 0) {
				if (error != EJUSTRETURN)
					m_freem(m);
				goto next;
			}
		}
		if (error != 0 || ((m->m_flags & M_PROMISC) != 0)) {
			m_freem(m);
			goto next;
		}

		/* Lookup the protocol attachment to this interface */
		if (protocol_family == 0) {
			ifproto = NULL;
		} else if (last_ifproto != NULL && last_ifproto->ifp == ifp &&
		    (last_ifproto->protocol_family == protocol_family)) {
			VERIFY(ifproto == NULL);
			ifproto = last_ifproto;
			if_proto_ref(last_ifproto);
		} else {
			VERIFY(ifproto == NULL);
			ifnet_lock_shared(ifp);
			/* callee holds a proto refcnt upon success */
			ifproto	= find_attached_proto(ifp, protocol_family);
			ifnet_lock_done(ifp);
		}
		if (ifproto == NULL) {
			/* no protocol for this packet, discard */
			m_freem(m);
			goto next;
		}
		if (ifproto != last_ifproto) {
			if (last_ifproto != NULL) {
				/* pass up the list for the previous protocol */
				dlil_ifproto_input(last_ifproto, pkt_first);
				pkt_first = NULL;
				if_proto_free(last_ifproto);
			}
			last_ifproto = ifproto;
			if_proto_ref(ifproto);
		}
		/* extend the list */
		m->m_pkthdr.pkt_hdr = frame_header;
		if (pkt_first == NULL) {
			pkt_first = m;
		} else {
			*pkt_next = m;
		}
		pkt_next = &m->m_nextpkt;

next:
		if (next_packet == NULL && last_ifproto != NULL) {
			/* pass up the last list of packets */
			dlil_ifproto_input(last_ifproto, pkt_first);
			if_proto_free(last_ifproto);
			last_ifproto = NULL;
		}
		if (ifproto != NULL) {
			if_proto_free(ifproto);
			ifproto = NULL;
		}

		m = next_packet;

		/* update the driver's multicast filter, if needed */
		if (ifp->if_updatemcasts > 0 && if_mcasts_update(ifp) == 0)
			ifp->if_updatemcasts = 0;
		if (iorefcnt == 1)
			ifnet_decr_iorefcnt(ifp);
	}

	KERNEL_DEBUG(DBG_FNC_DLIL_INPUT | DBG_FUNC_END, 0, 0, 0, 0, 0);
}