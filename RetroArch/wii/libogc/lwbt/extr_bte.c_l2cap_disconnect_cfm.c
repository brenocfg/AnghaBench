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
typedef  scalar_t__ u32 ;
struct l2cap_pcb {int dummy; } ;
struct bte_pcb {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* disconn_cfm ) (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ;scalar_t__ state; int /*<<< orphan*/  err; int /*<<< orphan*/ * ctl_pcb; int /*<<< orphan*/ * data_pcb; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  HCI_OTHER_END_TERMINATED_CONN_USER_ENDED ; 
#define  HIDP_CONTROL_CHANNEL 129 
#define  HIDP_DATA_CHANNEL 128 
 scalar_t__ STATE_DISCONNECTED ; 
 int /*<<< orphan*/  __bte_close_ctrl_queue (struct bte_pcb*) ; 
 int /*<<< orphan*/  hci_cmd_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_disconnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2ca_disconnect_req (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*,struct l2cap_pcb*)) ; 
 int /*<<< orphan*/  l2cap_close (int /*<<< orphan*/ *) ; 
 int l2cap_psm (struct l2cap_pcb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ; 

err_t l2cap_disconnect_cfm(void *arg, struct l2cap_pcb *pcb)
{
	struct bte_pcb *bte = (struct bte_pcb*)arg;

	if(bte==NULL) return ERR_OK;

	switch(l2cap_psm(pcb)) {
		case HIDP_CONTROL_CHANNEL:
			l2cap_close(bte->ctl_pcb);
			bte->ctl_pcb = NULL;
			if(bte->data_pcb!=NULL)
				l2ca_disconnect_req(bte->data_pcb,l2cap_disconnect_cfm);
			break;
		case HIDP_DATA_CHANNEL:
			l2cap_close(bte->data_pcb);
			bte->data_pcb = NULL;
			if(bte->ctl_pcb!=NULL)
				l2ca_disconnect_req(bte->ctl_pcb,l2cap_disconnect_cfm);
			break;
	}
	if(bte->data_pcb==NULL && bte->ctl_pcb==NULL) {
		bte->err = ERR_OK;
		bte->state = (u32)STATE_DISCONNECTED;
		__bte_close_ctrl_queue(bte);
		if(bte->disconn_cfm!=NULL) bte->disconn_cfm(bte->cbarg,bte,ERR_OK);

		hci_cmd_complete(NULL);
		hci_disconnect(&(bte->bdaddr),HCI_OTHER_END_TERMINATED_CONN_USER_ENDED);
	}

	return ERR_OK;
}