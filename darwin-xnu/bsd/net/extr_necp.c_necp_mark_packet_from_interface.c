#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  necp_last_interface_index; } ;
struct TYPE_6__ {TYPE_1__ necp_mtag; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;
typedef  TYPE_3__* ifnet_t ;
struct TYPE_7__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_PKTHDR ; 

int
necp_mark_packet_from_interface(struct mbuf *packet, ifnet_t interface)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (EINVAL);
	}

	// Mark ID for Pass and IP Tunnel
	if (interface != NULL) {
		packet->m_pkthdr.necp_mtag.necp_last_interface_index = interface->if_index;
	}

	return (0);
}