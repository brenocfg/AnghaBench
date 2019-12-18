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
struct bte_pcb {scalar_t__ err; int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* conn_cfm ) (int /*<<< orphan*/ ,struct bte_pcb*,scalar_t__) ;scalar_t__ state; struct l2cap_pcb* ctl_pcb; struct l2cap_pcb* data_pcb; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 scalar_t__ ERR_CONN ; 
 scalar_t__ ERR_OK ; 
#define  HIDP_CONTROL_CHANNEL 129 
#define  HIDP_DATA_CHANNEL 128 
 scalar_t__ STATE_CONNECTED ; 
 int /*<<< orphan*/  bte_process_input ; 
 int /*<<< orphan*/  l2cap_close (struct l2cap_pcb*) ; 
 int /*<<< orphan*/  l2cap_disconnect_ind (struct l2cap_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_disconnected_ind ; 
 int l2cap_psm (struct l2cap_pcb*) ; 
 int /*<<< orphan*/  l2cap_recv (struct l2cap_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bte_pcb*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct bte_pcb*,scalar_t__) ; 

err_t l2cap_accepted(void *arg,struct l2cap_pcb *l2cappcb,err_t err)
{
	struct bte_pcb *btepcb = (struct bte_pcb*)arg;

	//printf("l2cap_accepted(%02x)\n",err);
	if(err==ERR_OK) {
		l2cap_recv(l2cappcb,bte_process_input);
		l2cap_disconnect_ind(l2cappcb,l2cap_disconnected_ind);
		switch(l2cap_psm(l2cappcb)) {
			case HIDP_CONTROL_CHANNEL:
				btepcb->ctl_pcb = l2cappcb;
				break;
			case HIDP_DATA_CHANNEL:
				btepcb->data_pcb = l2cappcb;
				break;
		}
		if(btepcb->data_pcb && btepcb->ctl_pcb) {
			btepcb->err = ERR_OK;
			btepcb->state = (u32)STATE_CONNECTED;
			if(btepcb->conn_cfm) btepcb->conn_cfm(btepcb->cbarg,btepcb,ERR_OK);
		}
	} else {
		l2cap_close(l2cappcb);
		btepcb->err = ERR_CONN;
		btepcb->conn_cfm(btepcb->cbarg,btepcb,ERR_CONN);
	}

	return ERR_OK;
}