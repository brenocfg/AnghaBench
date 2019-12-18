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
struct TYPE_2__ {int /*<<< orphan*/  pkt_flags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  PKTF_KEEPALIVE ; 

int
necp_mark_packet_as_keepalive(struct mbuf *packet, bool is_keepalive)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (EINVAL);
	}

	if (is_keepalive) {
		packet->m_pkthdr.pkt_flags |= PKTF_KEEPALIVE;
	} else {
		packet->m_pkthdr.pkt_flags &= ~PKTF_KEEPALIVE;
	}

	return (0);
}