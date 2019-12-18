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
struct uip_tcp_pcb {int state; } ;
typedef  scalar_t__ s8_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcbs; } ;

/* Variables and functions */
#define  UIP_CLOSED 133 
#define  UIP_CLOSE_WAIT 132 
 scalar_t__ UIP_ERR_OK ; 
#define  UIP_ESTABLISHED 131 
 int UIP_FIN_WAIT_1 ; 
 int UIP_LAST_ACK ; 
#define  UIP_LISTEN 130 
#define  UIP_SYN_RCVD 129 
#define  UIP_SYN_SENT 128 
 int /*<<< orphan*/  UIP_TCP_FIN ; 
 int /*<<< orphan*/  memb_free (int /*<<< orphan*/ *,struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_listen_tcp_pcbs ; 
 struct uip_tcp_pcb* uip_tcp_active_pcbs ; 
 TYPE_1__ uip_tcp_listen_pcbs ; 
 int /*<<< orphan*/  uip_tcp_pcbremove (struct uip_tcp_pcb**,struct uip_tcp_pcb*) ; 
 int /*<<< orphan*/  uip_tcp_pcbs ; 
 scalar_t__ uip_tcp_sendctrl (struct uip_tcp_pcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uip_tcpoutput (struct uip_tcp_pcb*) ; 

s8_t uip_tcp_close(struct uip_tcp_pcb *pcb)
{
	s8_t err;

	switch(pcb->state) {
		case UIP_CLOSED:
			err = UIP_ERR_OK;
			memb_free(&uip_tcp_pcbs,pcb);
			pcb = NULL;
			break;
		case UIP_LISTEN:
			err = UIP_ERR_OK;
			uip_tcp_pcbremove((struct uip_tcp_pcb**)&uip_tcp_listen_pcbs.pcbs,pcb);
			memb_free(&uip_listen_tcp_pcbs,pcb);
			pcb = NULL;
			break;
		case UIP_SYN_SENT:
			err = UIP_ERR_OK;
			uip_tcp_pcbremove(&uip_tcp_active_pcbs,pcb);
			memb_free(&uip_tcp_pcbs,pcb);
			pcb = NULL;
			break;
		case UIP_SYN_RCVD:
		case UIP_ESTABLISHED:
			err = uip_tcp_sendctrl(pcb,UIP_TCP_FIN);
			if(err==UIP_ERR_OK) pcb->state = UIP_FIN_WAIT_1;
			break;
		case UIP_CLOSE_WAIT:
			err = uip_tcp_sendctrl(pcb,UIP_TCP_FIN);
			if(err==UIP_ERR_OK) pcb->state = UIP_LAST_ACK;
			break;
		default:
			err	= UIP_ERR_OK;
			pcb = NULL;
			break;
	}
	if(pcb!=NULL && err==UIP_ERR_OK) uip_tcpoutput(pcb);

	return err;
}