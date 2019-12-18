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
typedef  int /*<<< orphan*/  u8_t ;
struct l2cap_pcb {int /*<<< orphan*/  state; int /*<<< orphan*/  remote_bdaddr; struct l2cap_pcb* next; } ;
struct bd_addr {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  L2CAP_CLOSED ; 
 int /*<<< orphan*/  L2CA_ACTION_DISCONN_IND (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ bd_addr_cmp (int /*<<< orphan*/ *,struct bd_addr*) ; 
 struct l2cap_pcb* l2cap_active_pcbs ; 
 int /*<<< orphan*/  l2cap_disconnect_bb_cb (struct bd_addr*,int /*<<< orphan*/ ) ; 

void lp_disconnect_ind(struct bd_addr *bdaddr,u8_t reason)
{
	struct l2cap_pcb *pcb, *tpcb;
	err_t ret;

	(void)ret;

	for(pcb = l2cap_active_pcbs; pcb != NULL;) {
		tpcb = pcb->next;
		LOG("lp_disconnect_ind: Find a pcb with a matching Bluetooth address\n");
		/* All PCBs with matching Bluetooth address have been disconnected */
		if(bd_addr_cmp(&(pcb->remote_bdaddr), bdaddr)) {// && pcb->state != L2CAP_CLOSED) {
			pcb->state = L2CAP_CLOSED;
			LOG("lp_disconnect_ind: Notify application\n");
			L2CA_ACTION_DISCONN_IND(pcb,ERR_OK,ret);
		}
		pcb = tpcb;
	}
	if(l2cap_disconnect_bb_cb) l2cap_disconnect_bb_cb(bdaddr,reason);
}