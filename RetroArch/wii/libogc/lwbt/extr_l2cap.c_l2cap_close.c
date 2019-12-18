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
struct l2cap_sig {scalar_t__ state; struct l2cap_sig* next; struct l2cap_sig* unrsp_sigs; } ;
struct l2cap_pcb {scalar_t__ state; struct l2cap_pcb* next; struct l2cap_pcb* unrsp_sigs; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 scalar_t__ L2CAP_LISTEN ; 
 int /*<<< orphan*/  L2CAP_RMV (struct l2cap_sig**,struct l2cap_sig*) ; 
 int /*<<< orphan*/  btmemb_free (int /*<<< orphan*/ *,struct l2cap_sig*) ; 
 struct l2cap_sig* l2cap_active_pcbs ; 
 int /*<<< orphan*/  l2cap_listen_pcbs ; 
 int /*<<< orphan*/  l2cap_listenpcbs ; 
 int /*<<< orphan*/  l2cap_pcbs ; 
 int /*<<< orphan*/  l2cap_sigs ; 

err_t l2cap_close(struct l2cap_pcb *pcb)
{
	struct l2cap_sig *tmpsig;

	if(pcb->state == L2CAP_LISTEN) {
		L2CAP_RMV((struct l2cap_pcb**)((void*)&(l2cap_listen_pcbs)), pcb);
		btmemb_free(&l2cap_listenpcbs, pcb);
	} else {
		L2CAP_RMV(&(l2cap_active_pcbs), pcb);
		/* Free any unresponded signals */
		while(pcb->unrsp_sigs != NULL) {
			tmpsig = pcb->unrsp_sigs;
			pcb->unrsp_sigs = pcb->unrsp_sigs->next;
			btmemb_free(&l2cap_sigs, tmpsig);
		}

		btmemb_free(&l2cap_pcbs, pcb);
	}
	pcb = NULL;
	return ERR_OK;
}