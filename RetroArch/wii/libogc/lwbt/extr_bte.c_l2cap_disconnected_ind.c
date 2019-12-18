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
typedef  void* u32 ;
struct l2cap_pcb {int dummy; } ;
struct bte_pcb {int /*<<< orphan*/  cbarg; int /*<<< orphan*/  (* disconn_cfm ) (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ;void* state; int /*<<< orphan*/  err; int /*<<< orphan*/ * ctl_pcb; int /*<<< orphan*/ * data_pcb; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
#define  HIDP_CONTROL_CHANNEL 129 
#define  HIDP_DATA_CHANNEL 128 
 scalar_t__ STATE_DISCONNECTED ; 
 scalar_t__ STATE_DISCONNECTING ; 
 int /*<<< orphan*/  __bte_close_ctrl_queue (struct bte_pcb*) ; 
 int /*<<< orphan*/  l2cap_close (int /*<<< orphan*/ *) ; 
 int l2cap_psm (struct l2cap_pcb*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bte_pcb*,int /*<<< orphan*/ ) ; 

err_t l2cap_disconnected_ind(void *arg, struct l2cap_pcb *pcb, err_t err)
{
	struct bte_pcb *bte = (struct bte_pcb*)arg;

	if(bte==NULL) return ERR_OK;

	bte->state = (u32)STATE_DISCONNECTING;
	switch(l2cap_psm(pcb)) {
		case HIDP_CONTROL_CHANNEL:
			l2cap_close(bte->ctl_pcb);
			bte->ctl_pcb = NULL;
			break;
		case HIDP_DATA_CHANNEL:
			l2cap_close(bte->data_pcb);
			bte->data_pcb = NULL;
			break;
	}
	if(bte->data_pcb==NULL && bte->ctl_pcb==NULL) {
		bte->err = ERR_OK;
		bte->state = (u32)STATE_DISCONNECTED;
		__bte_close_ctrl_queue(bte);
		if(bte->disconn_cfm!=NULL) bte->disconn_cfm(bte->cbarg,bte,ERR_OK);
	}
	return ERR_OK;
}