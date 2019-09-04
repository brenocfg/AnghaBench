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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  necp_route_rule_id; } ;
struct TYPE_4__ {TYPE_1__ necp_mtag; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 

u_int32_t
necp_get_route_rule_id_from_packet(struct mbuf *packet)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (0);
	}

	return (packet->m_pkthdr.necp_mtag.necp_route_rule_id);
}