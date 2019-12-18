#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* lacpdu_ref ;
typedef  int /*<<< orphan*/  lacp_actor_partner_tlv_ref ;
typedef  int /*<<< orphan*/ * bondport_ref ;
struct TYPE_6__ {int /*<<< orphan*/  la_actor_tlv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAEventPacket ; 
 int /*<<< orphan*/  LAEventPortMoved ; 
 int /*<<< orphan*/  bondport_mux_machine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bondport_periodic_transmit_machine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  bondport_receive_machine (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * ifbond_list_find_moved_port (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
bondport_receive_lacpdu(bondport_ref p, lacpdu_ref in_lacpdu_p)
{
    bondport_ref		moved_port;

    moved_port
	= ifbond_list_find_moved_port(p, (const lacp_actor_partner_tlv_ref)
				      &in_lacpdu_p->la_actor_tlv);
    if (moved_port != NULL) {
	bondport_receive_machine(moved_port, LAEventPortMoved, NULL);
    }
    bondport_receive_machine(p, LAEventPacket, in_lacpdu_p);
    bondport_mux_machine(p, LAEventPacket, in_lacpdu_p);
    bondport_periodic_transmit_machine(p, LAEventPacket, in_lacpdu_p);
    return;
}