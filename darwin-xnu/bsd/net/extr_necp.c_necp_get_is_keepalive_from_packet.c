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
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int FALSE ; 
 int M_PKTHDR ; 
 int PKTF_KEEPALIVE ; 

bool
necp_get_is_keepalive_from_packet(struct mbuf *packet)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (FALSE);
	}

	return (packet->m_pkthdr.pkt_flags & PKTF_KEEPALIVE);
}