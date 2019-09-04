#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  TYPE_1__* mbuf_t ;
struct TYPE_5__ {int /*<<< orphan*/ * m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_input (TYPE_1__*) ; 
 int /*<<< orphan*/  ip_input_process_list (TYPE_1__*) ; 

__attribute__((used)) static void
ip_proto_input(protocol_family_t protocol, mbuf_t packet_list)
{
#pragma unused(protocol)

	if (packet_list->m_nextpkt != NULL) {
		ip_input_process_list(packet_list);
	} else {
		/*
		 * XXX remove this path if ip_input_process_list is proven
		 * to be stable and has minimum overhead on most platforms.
		 */
		ip_input(packet_list);
	}
}