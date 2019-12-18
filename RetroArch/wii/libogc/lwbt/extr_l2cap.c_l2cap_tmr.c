#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct l2cap_sig {scalar_t__ rtx; scalar_t__ nrtx; scalar_t__ ertx; struct l2cap_sig* next; } ;
struct TYPE_2__ {int outflushto; scalar_t__ cfgto; int l2capcfg; } ;
struct l2cap_pcb {scalar_t__ state; TYPE_1__ cfg; struct l2cap_sig* unrsp_sigs; struct l2cap_pcb* next; } ;
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OK ; 
 int L2CAP_CFG_IR ; 
 scalar_t__ L2CAP_CFG_TO ; 
 void* L2CAP_CLOSED ; 
 scalar_t__ L2CAP_CONFIG ; 
 int /*<<< orphan*/  L2CAP_CONN_CFG_TO ; 
 scalar_t__ L2CAP_RTX ; 
 int /*<<< orphan*/  L2CA_ACTION_CONN_CFM (struct l2cap_pcb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_ACTION_CONN_IND (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_ACTION_DISCONN_IND (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CA_ACTION_TO_IND (struct l2cap_pcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  l2ca_disconnect_req (struct l2cap_pcb*,int /*<<< orphan*/ *) ; 
 struct l2cap_pcb* l2cap_active_pcbs ; 
 int /*<<< orphan*/  l2cap_rexmit_signal (struct l2cap_pcb*,struct l2cap_sig*) ; 

void l2cap_tmr()
{
	struct l2cap_sig *sig;
	struct l2cap_pcb *pcb;
	err_t ret;

	(void) ret;

	/* Step through all of the active pcbs */
	for(pcb = l2cap_active_pcbs; pcb != NULL; pcb = pcb->next) {
		/* Step through any unresponded signals */
		for(sig = pcb->unrsp_sigs; sig != NULL; sig = sig->next) {
			/* Check if channel is not reliable */
			if(pcb->cfg.outflushto < 0xFFFF) {
				/* Check if rtx is active. Otherwise ertx is active */
				if(sig->rtx > 0) {
					/* Adjust rtx timer */
					--sig->rtx;
					/* Check if rtx has expired */
					if(sig->rtx == 0) {
						if(sig->nrtx == 0) {
							/* Move pcb to closed state */
							pcb->state = L2CAP_CLOSED;
							/* Indicate disconnect to upper layer */
							LOG("l2cap_tmr: Max number of retransmissions (rtx) has expired\n");
							L2CA_ACTION_DISCONN_IND(pcb,ERR_OK,ret);
						} else {
							--sig->nrtx;
							/* Indicate timeout to upper layer */
							L2CA_ACTION_TO_IND(pcb,ERR_OK,ret);
							/* Retransmitt signal w timeout doubled */
							sig->rtx += sig->rtx;
							ret = l2cap_rexmit_signal(pcb, sig);
						}
					} /* if */
				} else {
					/* Adjust ertx timer */
					--sig->ertx;
					/* Check if ertx has expired */
					if(sig->ertx == 0) {
						if(sig->nrtx == 0) {
							/* Move pcb to closed state */
							pcb->state = L2CAP_CLOSED;
							/* Indicate disconnect to upper layer */
							LOG("l2cap_tmr: Max number of retransmissions (ertx) has expired\n");
							L2CA_ACTION_DISCONN_IND(pcb,ERR_OK,ret);
						} else {
							--sig->nrtx;
							/* Indicate timeout to upper layer */
							L2CA_ACTION_TO_IND(pcb,ERR_OK,ret);
							/* Disable ertx, activate rtx and retransmitt signal */
							sig->ertx = 0;
							sig->rtx = L2CAP_RTX;
							ret = l2cap_rexmit_signal(pcb, sig);
						}
					} /* if */
				} /* else */
			} /* if */
		} /* for */

		/* Check configuration timer */
		if(pcb->state == L2CAP_CONFIG) {
			/* Check if configuration timer is active */
			if(pcb->cfg.cfgto > 0) {
				--pcb->cfg.cfgto;
				//LOG("l2cap_tmr: Configuration timer = %d\n", pcb->cfg.cfgto);
				/* Check if config timer has expired */
				if(pcb->cfg.cfgto == 0) {
					/* Connection attempt failed. Disconnect */
					l2ca_disconnect_req(pcb, NULL);
					/* Notify the application that the connection attempt failed */
					if(pcb->cfg.l2capcfg & L2CAP_CFG_IR) {
						L2CA_ACTION_CONN_CFM(pcb, L2CAP_CONN_CFG_TO, 0x0000, ret);
					} else {
						L2CA_ACTION_CONN_IND(pcb, ERR_OK, ret);
					}
					pcb->cfg.cfgto = L2CAP_CFG_TO; /* Reset timer */
				}
			}
		}
	} /* for */
}