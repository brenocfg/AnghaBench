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
struct TYPE_3__ {scalar_t__ necp_policy_id; } ;
struct TYPE_4__ {TYPE_1__ necp_mtag; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;
typedef  scalar_t__ necp_kernel_policy_id ;

/* Variables and functions */
 int EINVAL ; 
 int M_PKTHDR ; 
 scalar_t__ NECP_KERNEL_POLICY_ID_NONE ; 

int
necp_mark_packet_from_ip(struct mbuf *packet, necp_kernel_policy_id policy_id)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (EINVAL);
	}

	// Mark ID for Pass and IP Tunnel
	if (policy_id != NECP_KERNEL_POLICY_ID_NONE) {
		packet->m_pkthdr.necp_mtag.necp_policy_id = policy_id;
	} else {
		packet->m_pkthdr.necp_mtag.necp_policy_id = NECP_KERNEL_POLICY_ID_NONE;
	}

	return (0);
}