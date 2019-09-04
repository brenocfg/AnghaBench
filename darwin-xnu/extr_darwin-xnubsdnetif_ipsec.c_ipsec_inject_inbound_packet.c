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
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ipsec_demux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipsec_proto_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

errno_t
ipsec_inject_inbound_packet(ifnet_t	interface,
			    mbuf_t	packet)
{
#if IPSEC_NEXUS
	struct ipsec_pcb *pcb = ifnet_softc(interface);

	if (pcb->ipsec_use_netif) {
		lck_rw_lock_shared(&pcb->ipsec_pcb_lock);

		lck_mtx_lock(&pcb->ipsec_input_chain_lock);
		if (pcb->ipsec_input_chain != NULL) {
			pcb->ipsec_input_chain_last->m_nextpkt = packet;
		} else {
			pcb->ipsec_input_chain = packet;
		}
		while (packet->m_nextpkt) {
			VERIFY(packet != packet->m_nextpkt);
			packet = packet->m_nextpkt;
		}
		pcb->ipsec_input_chain_last = packet;
		lck_mtx_unlock(&pcb->ipsec_input_chain_lock);

		kern_channel_ring_t rx_ring = pcb->ipsec_netif_rxring;
		lck_rw_unlock_shared(&pcb->ipsec_pcb_lock);

		if (rx_ring != NULL) {
			kern_channel_notify(rx_ring, 0);
		}

		return (0);
	} else
#endif // IPSEC_NEXUS
	{
		errno_t error;
		protocol_family_t protocol;
		if ((error = ipsec_demux(interface, packet, NULL, &protocol)) != 0) {
			return error;
		}

		return ipsec_proto_input(interface, protocol, packet, NULL);
	}
}